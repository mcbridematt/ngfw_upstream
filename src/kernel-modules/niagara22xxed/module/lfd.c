#include "niagara_module.h"

static volatile long unsigned int lfd_active[MAX_CARD];
static struct timer_list lfd_timers       [MAX_CARD][MAX_PORT_PER_CARD / 2];
static uint8_t lfd_state[MAX_CARD][MAX_PORT_PER_CARD / 2];
static int lfd_count[MAX_CARD][MAX_PORT_PER_CARD / 2];

static void timer_proc(unsigned long data)
{
	int card = data / MAX_PORT_PER_CARD;
	int segment = data % MAX_PORT_PER_CARD;
	int port0, port1;

	port0 = port_get(card, segment, 0);
	port1 = port_get(card, segment, 1);
	DBG("%x.%x %1x%1x state=%d count=%d", card, segment, port0, port1, lfd_state[card][segment], lfd_count[card][segment]);
	switch (lfd_state[card][segment]) {
	case 0: if (port0 && port1) {
			lfd_state[card][segment] = 1;
			break;
	}
	case 1: if (!port0 && port1) {
			lfd_state[card][segment] = 2;
			port_set(card, segment, 0, 1);
			port_set(card, segment, 1, 0);
	} else if (port0 && !port1) {
			lfd_state[card][segment] = 3;
			port_set(card, segment, 0, 0);
			port_set(card, segment, 1, 1);
	}
		break;
	case 2: if (port0) {
			lfd_state[card][segment] = 4;
			port_set(card, segment, 0, 1);
			port_set(card, segment, 1, 1);
	}
		break;
	case 3: if (port1) {
			lfd_state[card][segment] = 4;
			port_set(card, segment, 0, 1);
			port_set(card, segment, 1, 1);
	}
		break;
	case 4: if (port0 && port1) {
			lfd_state[card][segment] = 1;
			lfd_count[card][segment] = LFD_MAX_CHECK_COUNT;
	} else { if (lfd_count[card][segment]) {
			 lfd_state[card][segment] = 4;
			 lfd_count[card][segment]--;
		 } else {
			 lfd_state[card][segment] = 0;
			 lfd_count[card][segment] = LFD_MAX_CHECK_COUNT;
		 } }
		break;
	default:
		MSG("Internal error - invlid lfd_state[%d][%d]", card, segment);
		lfd_state[card][segment] = 0;
	}
	mod_timer(&lfd_timers[card][segment], jiffies + LFD_PERIOD * HZ / 10);
}



int lfd_start(int card, int segment)
{
	struct timer_list *timer = &lfd_timers[card][segment];

	if (test_and_set_bit(segment, lfd_active + card)) return 0;
	init_timer(timer);
	timer->expires = jiffies + 1;
	timer->function = timer_proc;
	timer->data = (card * MAX_PORT_PER_CARD) + segment;
	lfd_state[card][segment] = 0;
	lfd_count[card][segment] = LFD_MAX_CHECK_COUNT;
	add_timer(timer);
	return 0;
}
int lfd_stop(int card, int segment)
{
	struct timer_list *timer = &lfd_timers[card][segment];

	if (!test_and_clear_bit(segment, lfd_active + card)) return 0;
	del_timer(timer);
	return 0;
}
int lfd_get(int card, int segment)
{
	return !!test_bit(segment, lfd_active + card);
}
