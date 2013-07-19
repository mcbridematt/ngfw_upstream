#define DECLARE_LOCK(name)\
static volatile long unsigned int name##_lock_bits = 0;\
static void name##_unlock(int card)\
{\
        clear_bit(card, &name##_lock_bits);\
}\
static void name##_lock(int card)\
{\
        while (test_and_set_bit(card, &name##_lock_bits))\
                udelay(10);\
}
