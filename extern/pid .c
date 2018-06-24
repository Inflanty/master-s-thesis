#include "pid.h"

#define ERR_SUM_MAX		1000

typedef double pid_param_t;
typedef double pid_err_t;

struct pid_param
{
	pid_param_t kp;
	pid_param_t ki;
	pid_param_t kd;
	pid_err_t err;
	pid_err_t err_sum;
	pid_err_t err_last;
};

static struct pid_param pid_parameters;

void pid_init(pid_param_t kp_set, pid_param_t ki_set, pid_param_t kd_set)
{
	pid_parameters = {.kp = kp_set, .ki = ki_set, .kd = kd_set, .err = 0, .err_sum = 0, err_last = 0,};
}

float pid_calculate(float set_val, float read_val)
{
	float err_d, u;

	pid_params.err = set_val - read_val;
	pid_params.err_sum += pid_params.err;

	if (pid_params.err_sum > ERR_SUM_MAX) {
		pid_params.err_sum = ERR_SUM_MAX;
	} else if (pid_params.err_sum < -ERR_SUM_MAX) {
		pid_params.err_sum = -ERR_SUM_MAX;
	}

	err_d = pid_params.err_last - pid_params.err;
	u = pid_params.kp * pid_params.err + pid_params.ki * pid_params.err_sum
			+ pid_params.kd * err_d;
	return u;
}
