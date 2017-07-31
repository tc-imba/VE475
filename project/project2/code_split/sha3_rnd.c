inline void sha3_rnd(sha3_state_array A, sha3_bits b, size_t ir)
{
    sha3_step_theta(A, b);
    sha3_step_rho(A, b);
    sha3_step_pi(A, b);
    sha3_step_chi(A, b);
    sha3_step_iota(A, b, ir);
}
