#include "../includes/minirt.h"

float ft_atof(const char *str)
{
    float result;
    float decimal_factor;
    int sign;
    int has_decimal;

    result = 0.0;
    decimal_factor = 0.1;
    sign = 1;
    has_decimal = 0;
    while (*str == ' ' || *str == '\t' || *str == '\n')
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str && ft_isdigit(*str))
    {
        result = result * 10.0 + (*str - '0');
        str++;
    }
    if (*str == '.')
    {
        str++;
        has_decimal = 1;
    }
    while (*str && ft_isdigit(*str))
    {
        result += (*str - '0') * decimal_factor;
        decimal_factor *= 0.1;
        str++;
    }
    return (result * sign);
}

// int main(void)
// {
//     printf("ft_atof(\"42.5\"): %f\n", ft_atof("42.5"));
//     printf("ft_atof(\"  -3.1415\"): %f\n", ft_atof("  -3.1415"));
//     printf("ft_atof(\"0.007\"): %f\n", ft_atof("0.007"));
//     printf("ft_atof(\"123\"): %f\n", ft_atof("123"));
//     return (0);
// }
