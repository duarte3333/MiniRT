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

void start_atof(t_atof *atof)
{
    atof->frac = 0.0f;
    atof->sig = 1.0f;
    atof->tmp = 0.0f;
    atof->size = 10.0f;
    atof->flag = 0;
}

double  ft_atof(char **line)
{
    t_atof atof;

    start_atof(&atof);
    while (**line && **line != ',' && **line != 32 && **line != 9)
    {
        if (!atof_sig(line, &atof.sig))
            break ;
        if (ft_isdigit(**line) && !atof.flag)
            atof.tmp = atof.tmp * 10.0f + (**line - 48);
        if (ft_isdigit(**line) && atof.flag)
        {
            atof.frac += (**line - 48) / atof.size;
            atof.size *= 10.0f;
        }
        if (**line == '.')
            atof.flag = 1;
        (*line)++;
    }
    while (**line && ((**line == 32 || **line == 9) || **line == ','))
        (*line)++;
    return ((atof.tmp + atof.frac) * atof.sig);
}

/* int main(void)
{
    char *line = "50.5734644853";
    printf("%s\n", line);
    printf("%.10f\n", ft_atof(&line, 1.0f, 0.0f, 0.0f));
    return (0);
} */