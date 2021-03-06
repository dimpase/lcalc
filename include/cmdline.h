/** @file cmdline.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22.3
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef CMDLINE_H
#define CMDLINE_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CMDLINE_PARSER_PACKAGE
/** @brief the program name (used for printing errors) */
#define CMDLINE_PARSER_PACKAGE "lcalc"
#endif

#ifndef CMDLINE_PARSER_PACKAGE_NAME
/** @brief the complete program name (used for help and version) */
#define CMDLINE_PARSER_PACKAGE_NAME "lcalc"
#endif

#ifndef CMDLINE_PARSER_VERSION
/** @brief the program version */
#define CMDLINE_PARSER_VERSION "1.3 Dec 1, 2009"
#endif

/** @brief Where the command line options are stored */
struct gengetopt_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  int value_flag;	/**< @brief compute L-function at x+iy. Should be used in conjuction with x and y options (default=off).  */
  const char *value_help; /**< @brief compute L-function at x+iy. Should be used in conjuction with x and y options help description.  */
  char * x_arg;	/**< @brief Used with value,value-line-segment, and zeros-interval options (default='.5').  */
  char * x_orig;	/**< @brief Used with value,value-line-segment, and zeros-interval options original value given at command line.  */
  const char *x_help; /**< @brief Used with value,value-line-segment, and zeros-interval options help description.  */
  char * y_arg;	/**< @brief Used with value,value-line-segment, and zeros-interval options (default='0').  */
  char * y_orig;	/**< @brief Used with value,value-line-segment, and zeros-interval options original value given at command line.  */
  const char *y_help; /**< @brief Used with value,value-line-segment, and zeros-interval options help description.  */
  char * value_file_arg;	/**< @brief compute L-function at points specified in file.  */
  char * value_file_orig;	/**< @brief compute L-function at points specified in file original value given at command line.  */
  const char *value_file_help; /**< @brief compute L-function at points specified in file help description.  */
  int value_line_segment_flag;	/**< @brief compute L-function along a line segment connecting (x+iy) to (X+iY) at number-sample points (default=off).  */
  const char *value_line_segment_help; /**< @brief compute L-function along a line segment connecting (x+iy) to (X+iY) at number-sample points help description.  */
  int use_dirichlet_series_flag;	/**< @brief compute values of the L-function using specified number of terms of the Dirichlet series rather than an approximate functional equation. (default=off).  */
  const char *use_dirichlet_series_help; /**< @brief compute values of the L-function using specified number of terms of the Dirichlet series rather than an approximate functional equation. help description.  */
  int number_terms_arg;	/**< @brief specify how many terms of the Dirichlet series, n <= <int>, to use. Can be used with --use-dirichlet-series or --rhs-explicit-formula options..  */
  char * number_terms_orig;	/**< @brief specify how many terms of the Dirichlet series, n <= <int>, to use. Can be used with --use-dirichlet-series or --rhs-explicit-formula options. original value given at command line.  */
  const char *number_terms_help; /**< @brief specify how many terms of the Dirichlet series, n <= <int>, to use. Can be used with --use-dirichlet-series or --rhs-explicit-formula options. help description.  */
  int hardy_flag;	/**< @brief compute the Hardy Z function, i.e. the L-function rotated to be real on the critical line (default=off).  */
  const char *hardy_help; /**< @brief compute the Hardy Z function, i.e. the L-function rotated to be real on the critical line help description.  */
  char * X_arg;	/**< @brief Used with value-line-segment (default='.5').  */
  char * X_orig;	/**< @brief Used with value-line-segment original value given at command line.  */
  const char *X_help; /**< @brief Used with value-line-segment help description.  */
  char * Y_arg;	/**< @brief Used with value-line-segment (default='100').  */
  char * Y_orig;	/**< @brief Used with value-line-segment original value given at command line.  */
  const char *Y_help; /**< @brief Used with value-line-segment help description.  */
  int number_samples_arg;	/**< @brief Used with value-line-segment, and interpolate options (default='1000').  */
  char * number_samples_orig;	/**< @brief Used with value-line-segment, and interpolate options original value given at command line.  */
  const char *number_samples_help; /**< @brief Used with value-line-segment, and interpolate options help description.  */
  char * zeros_arg;	/**< @brief number of zeros to find.  */
  char * zeros_orig;	/**< @brief number of zeros to find original value given at command line.  */
  const char *zeros_help; /**< @brief number of zeros to find help description.  */
  char * N_arg;	/**< @brief start after the Nth zero. For example -z 100 -N 1000 will search for 100 zeros after the 1000th zero..  */
  char * N_orig;	/**< @brief start after the Nth zero. For example -z 100 -N 1000 will search for 100 zeros after the 1000th zero. original value given at command line.  */
  const char *N_help; /**< @brief start after the Nth zero. For example -z 100 -N 1000 will search for 100 zeros after the 1000th zero. help description.  */
  char * NT_arg;	/**< @brief Compute N(T). Specify the value of T..  */
  char * NT_orig;	/**< @brief Compute N(T). Specify the value of T. original value given at command line.  */
  const char *NT_help; /**< @brief Compute N(T). Specify the value of T. help description.  */
  int zeros_interval_flag;	/**< @brief find zeros in an interval (1/2+ix,1/2+iy) using steps of size stepsize. Use with the x,y, and stepsize options (default=off).  */
  const char *zeros_interval_help; /**< @brief find zeros in an interval (1/2+ix,1/2+iy) using steps of size stepsize. Use with the x,y, and stepsize options help description.  */
  char * rhs_explicit_formula_arg;	/**< @brief Compute the rhs of the explicit formula with test function phi(t-x0), evaluated for x0 in [x,y], in increments of stepsize.
                                   Specify method: hermite_<integer>, or sinc_<integer>.
                                   Use with the --alpha --stepsize, -x, and -y options.
                                   For example --rhs-explicit-formula sinc_3 --alpha 4 -x 0 -y 100 --stepsize .1.  */
  char * rhs_explicit_formula_orig;	/**< @brief Compute the rhs of the explicit formula with test function phi(t-x0), evaluated for x0 in [x,y], in increments of stepsize.
                                   Specify method: hermite_<integer>, or sinc_<integer>.
                                   Use with the --alpha --stepsize, -x, and -y options.
                                   For example --rhs-explicit-formula sinc_3 --alpha 4 -x 0 -y 100 --stepsize .1 original value given at command line.  */
  const char *rhs_explicit_formula_help; /**< @brief Compute the rhs of the explicit formula with test function phi(t-x0), evaluated for x0 in [x,y], in increments of stepsize.
                                   Specify method: hermite_<integer>, or sinc_<integer>.
                                   Use with the --alpha --stepsize, -x, and -y options.
                                   For example --rhs-explicit-formula sinc_3 --alpha 4 -x 0 -y 100 --stepsize .1 help description.  */
  char * alpha_arg;	/**< @brief For use with --rhs-explicit-formula. Specifies the scaling factor to use..  */
  char * alpha_orig;	/**< @brief For use with --rhs-explicit-formula. Specifies the scaling factor to use. original value given at command line.  */
  const char *alpha_help; /**< @brief For use with --rhs-explicit-formula. Specifies the scaling factor to use. help description.  */
  char * stepsize_arg;	/**< @brief Used with zeros-interval or rhs-explicit-formula.  */
  char * stepsize_orig;	/**< @brief Used with zeros-interval or rhs-explicit-formula original value given at command line.  */
  const char *stepsize_help; /**< @brief Used with zeros-interval or rhs-explicit-formula help description.  */
  int derivative_arg;	/**< @brief compute derivative (up to 25th). use -d -1 to specify logarithmic derivative..  */
  char * derivative_orig;	/**< @brief compute derivative (up to 25th). use -d -1 to specify logarithmic derivative. original value given at command line.  */
  const char *derivative_help; /**< @brief compute derivative (up to 25th). use -d -1 to specify logarithmic derivative. help description.  */
  int elliptic_curve_flag;	/**< @brief specify an elliptic curve over Q. Use with the a1 a2 a3 a4 a6 options (default=off).  */
  const char *elliptic_curve_help; /**< @brief specify an elliptic curve over Q. Use with the a1 a2 a3 a4 a6 options help description.  */
  char * a1_arg;	/**< @brief Used with the elliptic-curve option.  */
  char * a1_orig;	/**< @brief Used with the elliptic-curve option original value given at command line.  */
  const char *a1_help; /**< @brief Used with the elliptic-curve option help description.  */
  char * a2_arg;	/**< @brief Used with the elliptic-curve option.  */
  char * a2_orig;	/**< @brief Used with the elliptic-curve option original value given at command line.  */
  const char *a2_help; /**< @brief Used with the elliptic-curve option help description.  */
  char * a3_arg;	/**< @brief Used with the elliptic-curve option.  */
  char * a3_orig;	/**< @brief Used with the elliptic-curve option original value given at command line.  */
  const char *a3_help; /**< @brief Used with the elliptic-curve option help description.  */
  char * a4_arg;	/**< @brief Used with the elliptic-curve option.  */
  char * a4_orig;	/**< @brief Used with the elliptic-curve option original value given at command line.  */
  const char *a4_help; /**< @brief Used with the elliptic-curve option help description.  */
  char * a6_arg;	/**< @brief Used with the elliptic-curve option.  */
  char * a6_orig;	/**< @brief Used with the elliptic-curve option original value given at command line.  */
  const char *a6_help; /**< @brief Used with the elliptic-curve option help description.  */
  char * file_input_arg;	/**< @brief input a file with basic L-function data.  */
  char * file_input_orig;	/**< @brief input a file with basic L-function data original value given at command line.  */
  const char *file_input_help; /**< @brief input a file with basic L-function data help description.  */
  char * url_arg;	/**< @brief input a web based file with basic L-function data. Specify the url of the file.  */
  char * url_orig;	/**< @brief input a web based file with basic L-function data. Specify the url of the file original value given at command line.  */
  const char *url_help; /**< @brief input a web based file with basic L-function data. Specify the url of the file help description.  */
  char * interpolate_arg;	/**< @brief interpolate between two L-functions and find their zeros. Should be used in conjunction with file-input.  */
  char * interpolate_orig;	/**< @brief interpolate between two L-functions and find their zeros. Should be used in conjunction with file-input original value given at command line.  */
  const char *interpolate_help; /**< @brief interpolate between two L-functions and find their zeros. Should be used in conjunction with file-input help description.  */
  char * output_character_arg;	/**< @brief if twisting, output the character (default='1').  */
  char * output_character_orig;	/**< @brief if twisting, output the character original value given at command line.  */
  const char *output_character_help; /**< @brief if twisting, output the character help description.  */
  int output_data_arg;	/**< @brief output basic data for the underlying L-function (default='10').  */
  char * output_data_orig;	/**< @brief output basic data for the underlying L-function original value given at command line.  */
  const char *output_data_help; /**< @brief output basic data for the underlying L-function help description.  */
  int verbose_arg;	/**< @brief verbosity > 0 outputs extra info (default='0').  */
  char * verbose_orig;	/**< @brief verbosity > 0 outputs extra info original value given at command line.  */
  const char *verbose_help; /**< @brief verbosity > 0 outputs extra info help description.  */
  int precision_arg;	/**< @brief number digits precision.  */
  char * precision_orig;	/**< @brief number digits precision original value given at command line.  */
  const char *precision_help; /**< @brief number digits precision help description.  */
  int sacrifice_arg;	/**< @brief number digits to sacrifice (default='3').  */
  char * sacrifice_orig;	/**< @brief number digits to sacrifice original value given at command line.  */
  const char *sacrifice_help; /**< @brief number digits to sacrifice help description.  */
  int rank_compute_flag;	/**< @brief compute the rank (default=off).  */
  const char *rank_compute_help; /**< @brief compute the rank help description.  */
  int rank_verify_arg;	/**< @brief verify if specified rank is correct.  */
  char * rank_verify_orig;	/**< @brief verify if specified rank is correct original value given at command line.  */
  const char *rank_verify_help; /**< @brief verify if specified rank is correct help description.  */
  int rank_limit_arg;	/**< @brief when doing quadratic twists limit to L-functions with specified rank.  */
  char * rank_limit_orig;	/**< @brief when doing quadratic twists limit to L-functions with specified rank original value given at command line.  */
  const char *rank_limit_help; /**< @brief when doing quadratic twists limit to L-functions with specified rank help description.  */
  int tau_flag;	/**< @brief Ramanujan tau L-function (weight 12, full level) (default=off).  */
  const char *tau_help; /**< @brief Ramanujan tau L-function (weight 12, full level) help description.  */
  int twist_quadratic_flag;	/**< @brief twist by fundamental quadratic characters, start <= discriminant <= finish. Use with start and finish options. (default=off).  */
  const char *twist_quadratic_help; /**< @brief twist by fundamental quadratic characters, start <= discriminant <= finish. Use with start and finish options. help description.  */
  char * start_arg;	/**< @brief Used with various twisting options.  */
  char * start_orig;	/**< @brief Used with various twisting options original value given at command line.  */
  const char *start_help; /**< @brief Used with various twisting options help description.  */
  char * finish_arg;	/**< @brief Used with various twisting options. Default has finish=start.  */
  char * finish_orig;	/**< @brief Used with various twisting options. Default has finish=start original value given at command line.  */
  const char *finish_help; /**< @brief Used with various twisting options. Default has finish=start help description.  */
  int twist_quadratic_even_flag;	/**< @brief twist by fundamental quadratic characters, even functional eqn, start <= discriminant <= finish (default=off).  */
  const char *twist_quadratic_even_help; /**< @brief twist by fundamental quadratic characters, even functional eqn, start <= discriminant <= finish help description.  */
  int twist_primitive_flag;	/**< @brief twist by all primitive Dirichlet characters with start <= conductor <= finish. For L-functions with complex Dirichlet coefficients, conjugate characters are considered equivalent (default=off).  */
  const char *twist_primitive_help; /**< @brief twist by all primitive Dirichlet characters with start <= conductor <= finish. For L-functions with complex Dirichlet coefficients, conjugate characters are considered equivalent help description.  */
  int twist_all_flag;	/**< @brief twist by all Dirichlet characters with start <= conductor <= finish. (default=off).  */
  const char *twist_all_help; /**< @brief twist by all Dirichlet characters with start <= conductor <= finish. help description.  */
  int twist_all_no_conj_pairs_flag;	/**< @brief twist by all Dirichlet characters with start <= conductor <= finish. For L-functions with complex Dirichlet coefficients, conjugate pairs of characters are considered equivalent (default=off).  */
  const char *twist_all_no_conj_pairs_help; /**< @brief twist by all Dirichlet characters with start <= conductor <= finish. For L-functions with complex Dirichlet coefficients, conjugate pairs of characters are considered equivalent help description.  */
  int twist_complex_no_conj_pairs_flag;	/**< @brief twist by all complex primitive Dirichlet characters with start <= conductor <= finish. For L-functions with complex Dirichlet coefficients, conjugate pairs of characters are considered equivalent (default=off).  */
  const char *twist_complex_no_conj_pairs_help; /**< @brief twist by all complex primitive Dirichlet characters with start <= conductor <= finish. For L-functions with complex Dirichlet coefficients, conjugate pairs of characters are considered equivalent help description.  */
  int twist_generic_flag;	/**< @brief twist by a generic complex Dirichlet characters with start <= conductor <= finish. (default=off).  */
  const char *twist_generic_help; /**< @brief twist by a generic complex Dirichlet characters with start <= conductor <= finish. help description.  */
  int degree_arg;	/**< @brief can only be used in conjuction with twist-primitive (?). Select characters of specified degree. Not yet implemented.  */
  char * degree_orig;	/**< @brief can only be used in conjuction with twist-primitive (?). Select characters of specified degree. Not yet implemented original value given at command line.  */
  const char *degree_help; /**< @brief can only be used in conjuction with twist-primitive (?). Select characters of specified degree. Not yet implemented help description.  */
  int openmp_arg;	/**< @brief whether to use openmp parallelization (beta- very little parallelization currently implemented) . Specify the number of threads to use..  */
  char * openmp_orig;	/**< @brief whether to use openmp parallelization (beta- very little parallelization currently implemented) . Specify the number of threads to use. original value given at command line.  */
  const char *openmp_help; /**< @brief whether to use openmp parallelization (beta- very little parallelization currently implemented) . Specify the number of threads to use. help description.  */
  int use_blfi_arg;	/**< @brief Can be used with use-dirichlet-series to compute values of the Dirichlet series using blf interpolation with specified interval length..  */
  char * use_blfi_orig;	/**< @brief Can be used with use-dirichlet-series to compute values of the Dirichlet series using blf interpolation with specified interval length. original value given at command line.  */
  const char *use_blfi_help; /**< @brief Can be used with use-dirichlet-series to compute values of the Dirichlet series using blf interpolation with specified interval length. help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int value_given ;	/**< @brief Whether value was given.  */
  unsigned int x_given ;	/**< @brief Whether x was given.  */
  unsigned int y_given ;	/**< @brief Whether y was given.  */
  unsigned int value_file_given ;	/**< @brief Whether value-file was given.  */
  unsigned int value_line_segment_given ;	/**< @brief Whether value-line-segment was given.  */
  unsigned int use_dirichlet_series_given ;	/**< @brief Whether use-dirichlet-series was given.  */
  unsigned int number_terms_given ;	/**< @brief Whether number-terms was given.  */
  unsigned int hardy_given ;	/**< @brief Whether hardy was given.  */
  unsigned int X_given ;	/**< @brief Whether X was given.  */
  unsigned int Y_given ;	/**< @brief Whether Y was given.  */
  unsigned int number_samples_given ;	/**< @brief Whether number-samples was given.  */
  unsigned int zeros_given ;	/**< @brief Whether zeros was given.  */
  unsigned int N_given ;	/**< @brief Whether N was given.  */
  unsigned int NT_given ;	/**< @brief Whether NT was given.  */
  unsigned int zeros_interval_given ;	/**< @brief Whether zeros-interval was given.  */
  unsigned int rhs_explicit_formula_given ;	/**< @brief Whether rhs-explicit-formula was given.  */
  unsigned int alpha_given ;	/**< @brief Whether alpha was given.  */
  unsigned int stepsize_given ;	/**< @brief Whether stepsize was given.  */
  unsigned int derivative_given ;	/**< @brief Whether derivative was given.  */
  unsigned int elliptic_curve_given ;	/**< @brief Whether elliptic-curve was given.  */
  unsigned int a1_given ;	/**< @brief Whether a1 was given.  */
  unsigned int a2_given ;	/**< @brief Whether a2 was given.  */
  unsigned int a3_given ;	/**< @brief Whether a3 was given.  */
  unsigned int a4_given ;	/**< @brief Whether a4 was given.  */
  unsigned int a6_given ;	/**< @brief Whether a6 was given.  */
  unsigned int file_input_given ;	/**< @brief Whether file-input was given.  */
  unsigned int url_given ;	/**< @brief Whether url was given.  */
  unsigned int interpolate_given ;	/**< @brief Whether interpolate was given.  */
  unsigned int output_character_given ;	/**< @brief Whether output-character was given.  */
  unsigned int output_data_given ;	/**< @brief Whether output-data was given.  */
  unsigned int verbose_given ;	/**< @brief Whether verbose was given.  */
  unsigned int precision_given ;	/**< @brief Whether precision was given.  */
  unsigned int sacrifice_given ;	/**< @brief Whether sacrifice was given.  */
  unsigned int rank_compute_given ;	/**< @brief Whether rank-compute was given.  */
  unsigned int rank_verify_given ;	/**< @brief Whether rank-verify was given.  */
  unsigned int rank_limit_given ;	/**< @brief Whether rank-limit was given.  */
  unsigned int tau_given ;	/**< @brief Whether tau was given.  */
  unsigned int twist_quadratic_given ;	/**< @brief Whether twist-quadratic was given.  */
  unsigned int start_given ;	/**< @brief Whether start was given.  */
  unsigned int finish_given ;	/**< @brief Whether finish was given.  */
  unsigned int twist_quadratic_even_given ;	/**< @brief Whether twist-quadratic-even was given.  */
  unsigned int twist_primitive_given ;	/**< @brief Whether twist-primitive was given.  */
  unsigned int twist_all_given ;	/**< @brief Whether twist-all was given.  */
  unsigned int twist_all_no_conj_pairs_given ;	/**< @brief Whether twist-all-no-conj-pairs was given.  */
  unsigned int twist_complex_no_conj_pairs_given ;	/**< @brief Whether twist-complex-no-conj-pairs was given.  */
  unsigned int twist_generic_given ;	/**< @brief Whether twist-generic was given.  */
  unsigned int degree_given ;	/**< @brief Whether degree was given.  */
  unsigned int openmp_given ;	/**< @brief Whether openmp was given.  */
  unsigned int use_blfi_given ;	/**< @brief Whether use-blfi was given.  */

} ;

/** @brief The additional parameters to pass to parser functions */
struct cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure gengetopt_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure gengetopt_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *gengetopt_args_info_purpose;
/** @brief the usage string of the program */
extern const char *gengetopt_args_info_usage;
/** @brief all the lines making the help output */
extern const char *gengetopt_args_info_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser (int argc, char **argv,
  struct gengetopt_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use cmdline_parser_ext() instead
 */
int cmdline_parser2 (int argc, char **argv,
  struct gengetopt_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_ext (int argc, char **argv,
  struct gengetopt_args_info *args_info,
  struct cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_dump(FILE *outfile,
  struct gengetopt_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_file_save(const char *filename,
  struct gengetopt_args_info *args_info);

/**
 * Print the help
 */
void cmdline_parser_print_help(void);
/**
 * Print the version
 */
void cmdline_parser_print_version(void);

/**
 * Initializes all the fields a cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void cmdline_parser_params_init(struct cmdline_parser_params *params);

/**
 * Allocates dynamically a cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized cmdline_parser_params structure
 */
struct cmdline_parser_params *cmdline_parser_params_create(void);

/**
 * Initializes the passed gengetopt_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void cmdline_parser_init (struct gengetopt_args_info *args_info);
/**
 * Deallocates the string fields of the gengetopt_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void cmdline_parser_free (struct gengetopt_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int cmdline_parser_required (struct gengetopt_args_info *args_info,
  const char *prog_name);

extern const char *cmdline_parser_output_character_values[];  /**< @brief Possible values for output-character. */


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* CMDLINE_H */
