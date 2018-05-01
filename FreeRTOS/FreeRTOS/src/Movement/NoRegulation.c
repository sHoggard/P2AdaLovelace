/*
 * NoRegulation.c
 *
 * Created: 2018-05-01 11:48:35
 *  Author: Sebastian Hoggard
 */ 

#ifdef NO_REGULATION
/**
 * Determines appropriate motor speed, given desired speed. 
 * Placeholder for PID. 
 */
void task_regulate(void *pvParameters)
{
	switch (mode)
	{
		// move duplicate code here?
		case 'd': 
			int16_t targetSpeed = regulated_speed.target;
			targetSpeed += MOTOR_THRESHOLD;
			if (targetSpeed > MAX_SPEED)
			{
				targetSpeed = MAX_SPEED;
			}
			regulated_speed.left = targetSpeed;
			regulated_speed.right = targetSpeed;
			break;
		case 'r':
			int16_t targetSpeed = regulated_speed.target;
			targetSpeed += MOTOR_THRESHOLD;
			if (targetSpeed > MAX_SPEED)
			{
				targetSpeed = MAX_SPEED;
			}
			regulated_speed.left = targetSpeed;
			regulated_speed.right = -targetSpeed;
			break;
	}
}
#endif