int main()
{
    int concat_num = concatenate(25, 52);
    printf("%d", concat_num);
}
int concatenate(int number1, int number2)
{
    int power = 10;
    while(number2 >= power)
    {
        power *= 10;
    }
    return number1 * power + number2;

}
