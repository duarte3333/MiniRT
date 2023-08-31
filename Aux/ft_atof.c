#include "../includes/minirt.h"

#include "../includes/minirt.h"

int atof_sig(char **line, double *sig)
{
    if (**line == '-')
        *sig *= -1;
    if (**line == '-' || **line == '+')
    {
        (*line)++;
        if (**line == '-' || **line == '+')
            return (0);
    }
    return (1);
}

double  ft_atof(char **line, double sig, double tmp, double frac)
{
    double n;
    double size;
    int flag;

    flag = 0;
    size = 10.0f;
    while (**line && **line != ',' && **line != 32 && **line != 9)
    {
        if (!atof_sig(line, &sig))
            break ;
        if (ft_isdigit(**line) && !flag)
            tmp = tmp * 10.0f + (**line - 48);
        if (ft_isdigit(**line) && flag)
        {
            frac += (**line - 48) / size;
            size *= 10.0f;
        }
        if (**line == '.')
            flag = 1;
        (*line)++;
    }
    while (**line && ((**line == 32 || **line == 9) || **line == ','))
        (*line)++;
    n = (tmp + frac) * sig;
    return (n);
}

/* int main(void)
{
    char *line = "50.5734644853";
    printf("%s\n", line);
    printf("%.10f\n", ft_atof(&line, 1.0f, 0.0f, 0.0f));
    return (0);
} */