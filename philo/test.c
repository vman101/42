#include "philo.h"

void	print_time(t_monitor *monitor)
{
	printf("%zu", monitor->start_time.tv_sec);
}

int main()
{
	t_monitor monitor;

	gettimeofday(&monitor.start_time, NULL);
	print_time(&monitor);
}
