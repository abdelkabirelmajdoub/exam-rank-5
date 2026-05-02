#!/bin/bash

# ==========================================
# إعدادات السكربت
# ==========================================
MY_CODE="life_copy.c"         # اسم ملفك
FRIEND_CODE="life_ael-majd/life.c" # اسم ملف صديقك

MY_EXEC="./my_out"
FRIEND_EXEC="./friend_out"

# ألوان للطباعة لتسهيل القراءة
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# ==========================================
# تجميع الأكواد (Compilation)
# ==========================================
echo "Compiling files..."
gcc -Wall -Wextra -Werror $MY_CODE -o $MY_EXEC
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: Failed to compile $MY_CODE${NC}"
    exit 1
fi

gcc -Wall -Wextra -Werror $FRIEND_CODE -o $FRIEND_EXEC
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: Failed to compile $FRIEND_CODE${NC}"
    exit 1
fi
echo "Compilation successful!"
echo "------------------------------------------------"

# ==========================================
# قائمة الاختبارات
# الصيغة: "العرض الطول الأجيال أوامر_الرسم"
# ==========================================
TESTS=(
    # الاختبارات الأساسية من الأمثلة
    "5 5 0 sdxddssaaww"
    "10 6 0 sdxssdswdxdddxsaddawxwdxwaa"
    "3 3 0 dxss"
    "3 3 1 dxss"
    "3 3 2 dxss"
    
    # اختبار المذبذب (Blinker) لعدة أجيال
    "3 3 5 dxss"
    "3 3 10 dxss"

    # شكل ثابت (Block) - يجب ألا يتغير
    "4 4 1 xdxsxsaxawx"
    "4 4 10 xdxsxsaxawx"

    # اختبار الخروج عن الحدود (Out of bounds) - حماية ضد Segfault
    "5 5 2 aaaaawwwwwwwdxx"
    "5 5 0 sssssdddddxxx"

    # لوحة فارغة (بدون رسم)
    "5 5 1 wawasd"

    # لوحة كبيرة وأجيال كثيرة
    "30 20 50 xdxddxxssxddww"
)

# ==========================================
# تنفيذ الاختبارات
# ==========================================
TEST_NUM=1
FAIL_COUNT=0

for TEST in "${TESTS[@]}"; do
    # استخراج المتغيرات من السلسلة النصية
    read -r W H ITER CMD <<< "$TEST"

    # تشغيل الكودين وحفظ المخرجات في ملفات مؤقتة
    echo -n "$CMD" | $MY_EXEC $W $H $ITER | cat -e > my_res.txt
    echo -n "$CMD" | $FRIEND_EXEC $W $H $ITER | cat -e > friend_res.txt

    # مقارنة المخرجات باستخدام diff
    DIFF_RESULT=$(diff my_res.txt friend_res.txt)

    if [ "$DIFF_RESULT" == "" ]; then
        echo -e "Test $TEST_NUM: [${GREEN}OK${NC}] - (W:$W H:$H I:$ITER CMD:'$CMD')"
    else
        echo -e "Test $TEST_NUM: [${RED}KO${NC}] - (W:$W H:$H I:$ITER CMD:'$CMD')"
        echo ">>> Difference found:"
        # عرض الاختلافات (اليسار كودك، اليمين كود صديقك)
        diff -y my_res.txt friend_res.txt
        echo "------------------------------------------------"
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
    TEST_NUM=$((TEST_NUM + 1))
done

# ==========================================
# النتيجة النهائية والترتيب
# ==========================================
echo "------------------------------------------------"
if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "${GREEN}ALL TESTS PASSED! Your code output matches exactly.${NC}"
else
    echo -e "${RED}$FAIL_COUNT tests failed. Check the differences above.${NC}"
fi

# تنظيف الملفات المؤقتة
rm -f my_res.txt friend_res.txt $MY_EXEC $FRIEND_EXEC