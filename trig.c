/*==================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *
 * File Name	:	trig.c
 *
 * Description	:   Program to create an array of x values (between
 *                  upper and lower limits, increasing in equal
 *                  steps, all supplied by the user), an array of
 *                  corresponding sin(x) values (calculated using a
 *                  function called calcsin) and to print a table of
 *                  these values (using a function called printout).
 *
 * Author		:	Donal C. Monahan
 *
 * Date			:	27-10-22
 *
 *==================================================================*/

#define MAXSIZE 50  /* maximum size allowable for arrays */
#define TOL 10e-6   /* minimum size allowable for term in series */
#define PI 3.141592654

/* function prototypes */
float calcsin(float, float);
void printout(float [], float [], int);

int main(void) {

    /* declare variables */
    float lo_lim, hi_lim, step_size, tolerance = TOL;
    int length;
    float x_values[MAXSIZE], sinx_values[MAXSIZE];

    /* prompt user to input limits and step size */
    printf("Enter the lower limit on x: ");
    scanf("%f", &lo_lim);
    printf("Enter the upper limit on x: ");
    scanf("%f", &hi_lim);
    printf("Enter the step size: ");
    scanf("%f", &step_size);

    /* calculate number of values of x for which sinx will be evaluated, i.e. length of x_values and sinx_values arrays */
    length = (hi_lim - lo_lim) / step_size + 1;

    /* error message if lo_lim >= hi_lim */
    if(lo_lim >= hi_lim)

        printf("\nError! Upper limit must be greater than lower limit.\n");

    /* error message if step_size <= 0 */
    else if(step_size <= 0)

        printf("\nError! Step size must be a positive number.\n");

    /* error message if length exceeds MAXSIZE */
    else if(length > MAXSIZE)

        printf("\nError! Try again for fewer than 50 values of x.\n");

    else{

        /* populate x_values and sinx_values arrays */
        for(int i = 0; i < length; i++) {

            x_values[i] = lo_lim + i * step_size; /* x_values[i] = lower limit + (step size * i)*/
            sinx_values[i] = calcsin(x_values[i], tolerance); /* call on calcsin function, with x_values[i] and tolerance as arguments */

        }

        /* print table header */
        printf("===============================\n");
        printf("|  x (radians)  |    sin(x)   |\n");
        printf("|=============================|\n");

        /* call printout function to print table body, where number of rows = length */
        printout(x_values, sinx_values, length);

        /* print table footer */
        printf("===============================\n");

    }

    return 0;

}

float calcsin(float x, float tolerance) {

    /* declare variables and initialize both to zero, as we will be adding to them in this function */
    float sinx = 0, term = 0;

    /* map x onto the range [0, 2 * PI], as sin(x + 2 * PI) = sin(x) */
    while(x > 2 * PI)

        x -= 2 * PI;

    while(x < 0)

        x += 2 *  PI;

    /* each term = (x ^ i) / (i!), so in each iteration of the loop, we 1: calculate (x ^ i) and
    2: (i!), 3: find their quotient (the variable called term), 4: the loop is broken when we have
    a term less than our tolerance, else 5: either add or subtract(alternating in each iteration)
    it to our total sum, sinx. */

    /* add term to sinx until term < tolerance */
    for(int i = 1; ; i += 2) {      /* no test expression defined here; test within loop will break loop when term < tolerance */

        /* 1: (x ^ i) */
        /* declare and initialize power_x to 1, as we will be multiplying it */
        float power_x = 1;

        /* multiply power_x by x, i times, giving us x ^ i */
        for(int j = 1; j <= i; j++)

            power_x *= x;

        /* 2: (i!) */
        /* declare and initialize i_factorial to 1, as we will be multiplying it */
        float i_factorial = 1;

        /* multiply x_factorial by k, from k = i down to k = 1, giving us i! */
        for(int k = i; k > 0; k--)

            i_factorial *= k;

        /* 3: term = (x ^ i) / (i!) */
        term = power_x / i_factorial;

        /* 4: break loop if term < tolerance */
        if(term < tolerance)

            break;

        /* 5: sinx = sinx +/- term */
        /* if i = 1, 5, 9, ... , (4n + 1), we add term to sinx */
        if((i + 1) % 4 != 0)

            sinx += term;

        /* if i = 3, 7, 11, ... , (4n - 1), we subtract term from sinx */
        else

            sinx -= term;

    }

    /* sinx is returned as the value of sinx_values[i] */
    return sinx;

}

void printout(float x_values[], float sinx_values[], int length) {

    /* print out a row of the table for each x value, with a column for x and a column for sinx */
    for(int i = 0; i < length; i++)

        printf("|%11.4f    |%10.4f   |\n", x_values[i], sinx_values[i]);

}
