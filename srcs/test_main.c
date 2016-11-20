//
// Created by Oleksandra Fedorova on 11/1/16.
//

#include <libftprintf.h>
#include <stdio.h>
#include <locale.h>

#include <wchar.h>

#include <limits.h>

int	main(void)
{
	//double par = 1.9999999999999;
	setlocale(LC_ALL, "");
	//printf("%d\n",printf("%lc\n", c)); // =4
	t_flags *flags = (t_flags *)malloc(sizeof(t_flags));
	flags->fd = 1;
	flags->capital = false;
	flags->precision = -1;
	(void)flags;
	//printf("%- - 5.*f", -4, 1.111111);
	//printf("lol  %+p", flags);

//	printf("\n%d\n", format_a(-0x1B8, flags));

	//printf("\x1b[33m" "Blue text");
	//format_s("\x1b[33m lol", flags);
	//write(1, "my:    \t", 8);
	//printf("\n%zu", format_A(par));

	printf(">%llu<", LLONG_MIN);

}

//p: - , field width