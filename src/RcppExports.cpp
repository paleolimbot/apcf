// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// geos_version
std::string geos_version();
RcppExport SEXP apcf_geos_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(geos_version());
    return rcpp_result_gen;
END_RCPP
}
// gdal_version
std::string gdal_version(const char* what);
RcppExport SEXP apcf_gdal_version(SEXP whatSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const char* >::type what(whatSEXP);
    rcpp_result_gen = Rcpp::wrap(gdal_version(what));
    return rcpp_result_gen;
END_RCPP
}
// pcf_envelope
Rcpp::DataFrame pcf_envelope(Rcpp::NumericVector sim, Rcpp::NumericVector dist, Rcpp::NumericVector ratio, Rcpp::NumericVector rs, double area, int nobj, double stoyan, int nrank);
RcppExport SEXP apcf_pcf_envelope(SEXP simSEXP, SEXP distSEXP, SEXP ratioSEXP, SEXP rsSEXP, SEXP areaSEXP, SEXP nobjSEXP, SEXP stoyanSEXP, SEXP nrankSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type sim(simSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type dist(distSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type ratio(ratioSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type rs(rsSEXP);
    Rcpp::traits::input_parameter< double >::type area(areaSEXP);
    Rcpp::traits::input_parameter< int >::type nobj(nobjSEXP);
    Rcpp::traits::input_parameter< double >::type stoyan(stoyanSEXP);
    Rcpp::traits::input_parameter< int >::type nrank(nrankSEXP);
    rcpp_result_gen = Rcpp::wrap(pcf_envelope(sim, dist, ratio, rs, area, nobj, stoyan, nrank));
    return rcpp_result_gen;
END_RCPP
}
// rand_dists_ratios
Rcpp::DataFrame rand_dists_ratios(const char* fn_pattern, const char* fn_area, const double max_dist, const unsigned int n_simulations, const unsigned int max_tries, const bool save_randomized_patterns, const char* save_basename, const bool verbose);
RcppExport SEXP apcf_rand_dists_ratios(SEXP fn_patternSEXP, SEXP fn_areaSEXP, SEXP max_distSEXP, SEXP n_simulationsSEXP, SEXP max_triesSEXP, SEXP save_randomized_patternsSEXP, SEXP save_basenameSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const char* >::type fn_pattern(fn_patternSEXP);
    Rcpp::traits::input_parameter< const char* >::type fn_area(fn_areaSEXP);
    Rcpp::traits::input_parameter< const double >::type max_dist(max_distSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type n_simulations(n_simulationsSEXP);
    Rcpp::traits::input_parameter< const unsigned int >::type max_tries(max_triesSEXP);
    Rcpp::traits::input_parameter< const bool >::type save_randomized_patterns(save_randomized_patternsSEXP);
    Rcpp::traits::input_parameter< const char* >::type save_basename(save_basenameSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(rand_dists_ratios(fn_pattern, fn_area, max_dist, n_simulations, max_tries, save_randomized_patterns, save_basename, verbose));
    return rcpp_result_gen;
END_RCPP
}
