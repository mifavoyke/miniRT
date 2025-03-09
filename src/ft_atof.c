#include "../includes/minirt.h"

double ft_atof(const char *str)
{
    double result;
    double fraction;
    int sign;
    int i;

    result = 0.0;
    fraction = 0.1;
    sign = 1;
    i = 0;
    if (!str || !str[i])
        return (0);
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (ft_isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        while (ft_isdigit(str[i]))
        {
            result += (str[i] - '0') * fraction;
            fraction *= 0.1;
            i++;
        }
    }
    result *= sign;
    if (result > INT_MAX || result < INT_MIN)
        return (INT_ERROR);
    return (result);
}

// int main(void)
// {
//     printf("ft_atoi(\"42\"): %d\n", ft_atoi("42"));
//     printf("ft_atoi(\"  -123\"): %d\n", ft_atoi("  -123"));
//     printf("ft_atoi(\"2147483647\"): %d\n", ft_atoi("2147483647")); // INT_MAX
//     printf("ft_atoi(\"-2147483648\"): %d\n", ft_atoi("-2147483648")); // INT_MIN
//     printf("ft_atoi(\"2147483648\"): %d\n", ft_atoi("2147483648")); // Overflow test
//     printf("ft_atoi(\"-2147483649\"): %d\n", ft_atoi("-2147483649")); // Underflow test
//     printf("ft_atoi(\"123abc\"): %d\n", ft_atoi("123abc"));

//     printf("ft_atof(\"42.5\"): %f\n", ft_atof("42.5"));
//     printf("ft_atof(\"  -3.1415\"): %f\n", ft_atof("  -3.1415"));
//     printf("ft_atof(\"0.007\"): %f\n", ft_atof("0.007"));
//     printf("ft_atof(\"123\"): %f\n", ft_atof("123"));
//     printf("ft_atof(\"340282346638528859811704183484516925500.000000\"): %f\n", ft_atof("340282346638528859811704183484516925440.000000"));
//     printf("FLT_MIN: %e\n", FLT_MIN);
//     printf("FLT_MAX: %e\n", FLT_MAX);
    
//     return (0);
// }
