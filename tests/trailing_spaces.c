/*
** EPITECH PROJECT, 2018
** trailing spaces
** File description:
** some dummy trailing spaces and tricky not trailing spaces
*/

typedef __attribute__ ((definetly_not_trailing)) NO;

void	test( int yeah, __attribute__ ((not_trailing)) char space , NO no )
{
	int	a    =     10;

	switch (space) {
	case (TRAILING):
		throw_an_error ();
	case (int) (STILL_TRAILING):
		throw_an_error( );
	case NOT_TRAILING:
		dont();
	case TRAILING_AGAIN :
		throw_an_error() ;
	default:
		¯\_(ツ)_/¯();
	}
	a = (NOT_TRAILING);
	a + = TRAILING_SPACE;
	a - = TRAILING_SPACE;
	a * = TRAILING_SPACE;
	a / = TRAILING_SPACE;
}
