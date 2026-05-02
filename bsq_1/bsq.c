# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
// دالة خوارزمية البحث عن المربع وطباعته
void solve_and_print(char **map, int rows, int cols, char e, char o, char f) {
    int max_sz = 0, max_r = 0, max_c = 0;
    int **dp = malloc(sizeof(int*) * rows);
    (void)e;
    for (int i = 0; i < rows; i++) {
        dp[i] = malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == o) {
                dp[i][j] = 0;
            } else {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    // إيجاد الحد الأدنى من الجيران الثلاثة
                    int min = dp[i-1][j];
                    if (dp[i][j-1] < min) min = dp[i][j-1];
                    if (dp[i-1][j-1] < min) min = dp[i-1][j-1];
                    dp[i][j] = min + 1;
                }
            }
            // التحديث إذا وجدنا مربعاً أكبر
            // نستخدم ">" وليس ">=" لضمان اختيار المربع الأقرب للأعلى ثم اليسار
            if (dp[i][j] > max_sz) {
                max_sz = dp[i][j];
                max_r = i;
                max_c = j;
            }
        }
    }

    // رسم حرف الامتلاء في المساحة الفائزة
    for (int i = max_r; i > max_r - max_sz; i--) {
        for (int j = max_c; j > max_c - max_sz; j--) {
            map[i][j] = f;
        }
    }

    // طباعة الخريطة وتحرير الذاكرة
    for (int i = 0; i < rows; i++) {
        fprintf(stdout, "%s\n", map[i]);
        free(map[i]);
        free(dp[i]);
    }
    free(map);
    free(dp);
}

// دالة قراءة الخريطة والتحقق من صحتها
int process_file(FILE *fp) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes = getline(&line, &len, fp);

    if (read_bytes <= 0) { free(line); return 0; }

    // إزالة سطر النهاية إذا كان موجوداً
    if (read_bytes > 0 && line[read_bytes - 1] == '\n') {
        line[read_bytes - 1] = '\0';
        read_bytes--;
    }

    // السطر الأول يجب أن يحتوي على الأقل على رقم و 3 حروف
    if (read_bytes < 4) { free(line); return 0; }

    char f = line[read_bytes - 1];
    char o = line[read_bytes - 2];
    char e = line[read_bytes - 3];

    // التحقق من عدم تطابق الحروف
    if (f == o || f == e || o == e) { free(line); return 0; }

    int rows = 0;
    for (int i = 0; i < read_bytes - 3; i++) {
        if (line[i] < '0' || line[i] > '9') { free(line); return 0; }
        rows = rows * 10 + (line[i] - '0');
    }
    free(line);

    if (rows <= 0) return 0;

    char **map = malloc(sizeof(char*) * rows);
    if (!map) return 0;

    int cols = -1;
    for (int i = 0; i < rows; i++) {
        line = NULL;
        len = 0;
        read_bytes = getline(&line, &len, fp);

        // خطأ: عدد الأسطر أقل من المتوقع
        if (read_bytes <= 0) {
            for (int j = 0; j < i; j++) free(map[j]);
            free(map); free(line); return 0;
        }

        if (line[read_bytes - 1] == '\n') {
            line[read_bytes - 1] = '\0';
            read_bytes--;
        }

        if (cols == -1) {
            cols = read_bytes;
            if (cols == 0) {
                for (int j = 0; j < i; j++) free(map[j]);
                free(map); free(line); return 0;
            }
        } else if (cols != read_bytes) {
            // خطأ: الأسطر ليست بنفس الطول
            for (int j = 0; j < i; j++) free(map[j]);
            free(map); free(line); return 0;
        }

        for (int j = 0; j < cols; j++) {
            // خطأ: وجود حرف غريب في الخريطة
            if (line[j] != e && line[j] != o) {
                for (int k = 0; k < i; k++) free(map[k]);
                free(map); free(line); return 0;
            }
        }
        map[i] = line;
    }

    // التحقق من عدم وجود أسطر إضافية أكثر من الرقم المحدد
    line = NULL;
    len = 0;
    if (getline(&line, &len, fp) > 0) {
        for (int j = 0; j < rows; j++) free(map[j]);
        free(map); free(line); return 0;
    }
    free(line);

    solve_and_print(map, rows, cols, e, o, f);
    return 1;
}

// الدالة الرئيسية
int main(int argc, char **argv) {
    if (argc == 1) {
        // قراءة من الإدخال القياسي إذا لم يتم توفير ملف
        if (!process_file(stdin)) {
            fprintf(stderr, "map error\n");
        }
    } else {
        // المرور على جميع الملفات الممررة
        for (int i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (!fp) {
                fprintf(stderr, "map error\n");
            } else {
                if (!process_file(fp)) {
                    fprintf(stderr, "map error\n");
                }
                fclose(fp);
            }
        }
    }
    return 0;
}