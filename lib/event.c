// Fuang.Cao <cavan.cfa@gmail.com> Wed May 25 10:12:17 CST 2011

#include <cavan.h>
#include <cavan/event.h>
#include <cavan/input.h>

char *cavan_event_tostring(struct input_event *event, char *text)
{
	const char *event_code = "UNKNOWN";

	switch (event->type)
	{
	case EV_SYN:
		switch (event->code)
		{
		case SYN_REPORT:
			text_copy(text, "SYN_REPORT");
			return text;

		case SYN_CONFIG:
			text_copy(text, "SYN_CONFIG");
			return text;

		case SYN_MT_REPORT:
			text_copy(text, "SYN_MT_REPORT");
			return text;

		default:
			sprintf(text, "EV_SYN[%d] = %d", event->code, event->value);
			return text;
		}
		break;
	case EV_KEY:
		switch (event->code)
		{
		case BTN_0:
			event_code = "BTN_0";
			break;
		case BTN_1:
			event_code = "BTN_1";
			break;
		case BTN_2:
			event_code = "BTN_2";
			break;
		case BTN_3:
			event_code = "BTN_3";
			break;
		case BTN_4:
			event_code = "BTN_4";
			break;
		case BTN_5:
			event_code = "BTN_5";
			break;
		case BTN_6:
			event_code = "BTN_6";
			break;
		case BTN_7:
			event_code = "BTN_7";
			break;
		case BTN_8:
			event_code = "BTN_8";
			break;
		case BTN_9:
			event_code = "BTN_9";
			break;
		case BTN_LEFT:
			event_code = "BTN_LEFT";
			break;
		case BTN_RIGHT:
			event_code = "BTN_RIGHT";
			break;
		case BTN_MIDDLE:
			event_code = "BTN_MIDDLE";
			break;
		case BTN_SIDE:
			event_code = "BTN_SIDE";
			break;
		case BTN_EXTRA:
			event_code = "BTN_EXTRA";
			break;
		case BTN_FORWARD:
			event_code = "BTN_FORWARD";
			break;
		case BTN_BACK:
			event_code = "BTN_BACK";
			break;
		case BTN_TASK:
			event_code = "BTN_TASK";
			break;
		case BTN_TRIGGER:
			event_code = "BTN_TRIGGER";
			break;
		case BTN_THUMB:
			event_code = "BTN_THUMB";
			break;
		case BTN_THUMB2:
			event_code = "BTN_THUMB2";
			break;
		case BTN_TOP:
			event_code = "BTN_TOP";
			break;
		case BTN_TOP2:
			event_code = "BTN_TOP2";
			break;
		case BTN_PINKIE:
			event_code = "BTN_PINKIE";
			break;
		case BTN_BASE:
			event_code = "BTN_BASE";
			break;
		case BTN_BASE2:
			event_code = "BTN_BASE2";
			break;
		case BTN_BASE3:
			event_code = "BTN_BASE3";
			break;
		case BTN_BASE4:
			event_code = "BTN_BASE4";
			break;
		case BTN_BASE5:
			event_code = "BTN_BASE5";
			break;
		case BTN_BASE6:
			event_code = "BTN_BASE6";
			break;
		case BTN_DEAD:
			event_code = "BTN_DEAD";
			break;
		case BTN_A:
			event_code = "BTN_A";
			break;
		case BTN_B:
			event_code = "BTN_B";
			break;
		case BTN_C:
			event_code = "BTN_C";
			break;
		case BTN_X:
			event_code = "BTN_X";
			break;
		case BTN_Y:
			event_code = "BTN_Y";
			break;
		case BTN_Z:
			event_code = "BTN_Z";
			break;
		case BTN_TL:
			event_code = "BTN_TL";
			break;
		case BTN_TR:
			event_code = "BTN_TR";
			break;
		case BTN_TL2:
			event_code = "BTN_TL2";
			break;
		case BTN_TR2:
			event_code = "BTN_TR2";
			break;
		case BTN_SELECT:
			event_code = "BTN_SELECT";
			break;
		case BTN_START:
			event_code = "BTN_START";
			break;
		case BTN_MODE:
			event_code = "BTN_MODE";
			break;
		case BTN_THUMBL:
			event_code = "BTN_THUMBL";
			break;
		case BTN_THUMBR:
			event_code = "BTN_THUMBR";
			break;
		case BTN_TOOL_PEN:
			event_code = "BTN_TOOL_PEN";
			break;
		case BTN_TOOL_RUBBER:
			event_code = "BTN_TOOL_RUBBER";
			break;
		case BTN_TOOL_BRUSH:
			event_code = "BTN_TOOL_BRUSH";
			break;
		case BTN_TOOL_PENCIL:
			event_code = "BTN_TOOL_PENCIL";
			break;
		case BTN_TOOL_AIRBRUSH:
			event_code = "BTN_TOOL_AIRBRUSH";
			break;
		case BTN_TOOL_FINGER:
			event_code = "BTN_TOOL_FINGER";
			break;
		case BTN_TOOL_MOUSE:
			event_code = "BTN_TOOL_MOUSE";
			break;
		case BTN_TOOL_LENS:
			event_code = "BTN_TOOL_LENS";
			break;
		case BTN_TOUCH:
			event_code = "BTN_TOUCH";
			break;
		case BTN_STYLUS:
			event_code = "BTN_STYLUS";
			break;
		case BTN_STYLUS2:
			event_code = "BTN_STYLUS2";
			break;
		case BTN_TOOL_DOUBLETAP:
			event_code = "BTN_TOOL_DOUBLETAP";
			break;
		case BTN_TOOL_TRIPLETAP:
			event_code = "BTN_TOOL_TRIPLETAP";
			break;
		case BTN_GEAR_DOWN:
			event_code = "BTN_GEAR_DOWN";
			break;
		case BTN_GEAR_UP:
			event_code = "BTN_GEAR_UP";
			break;
		default:
			sprintf(text, "EV_KEY[%d] = %d", event->code, event->value);
			return text;
		}
		break;
	case EV_REL:
		switch (event->code)
		{
		case REL_X:
			event_code = "REL_X";
			break;
		case REL_Y:
			event_code = "REL_Y";
			break;
		case REL_Z:
			event_code = "REL_Z";
			break;
		case REL_RX:
			event_code = "REL_RX";
			break;
		case REL_RY:
			event_code = "REL_RY";
			break;
		case REL_RZ:
			event_code = "REL_RZ";
			break;
		case REL_HWHEEL:
			event_code = "REL_HWHEEL";
			break;
		case REL_DIAL:
			event_code = "REL_DIAL";
			break;
		case REL_WHEEL:
			event_code = "REL_WHEEL";
			break;
		case REL_MISC:
			event_code = "REL_MISC";
			break;
		case REL_MAX:
			event_code = "REL_MAX";
			break;
		default:
			sprintf(text, "EV_REL[%d] = %d", event->code, event->value);
			return text;
		}
		break;
	case EV_ABS:
		switch (event->code)
		{
		case ABS_X:
			event_code = "ABS_X";
			break;
		case ABS_Y:
			event_code = "ABS_Y";
			break;
		case ABS_Z:
			event_code = "ABS_Z";
			break;
		case ABS_RX:
			event_code = "ABS_RX";
			break;
		case ABS_RY:
			event_code = "ABS_RY";
			break;
		case ABS_RZ:
			event_code = "ABS_RZ";
			break;
		case ABS_THROTTLE:
			event_code = "ABS_THROTTLE";
			break;
		case ABS_RUDDER:
			event_code = "ABS_RUDDER";
			break;
		case ABS_WHEEL:
			event_code = "ABS_WHEEL";
			break;
		case ABS_GAS:
			event_code = "ABS_GAS";
			break;
		case ABS_BRAKE:
			event_code = "ABS_BRAKE";
			break;
		case ABS_HAT0X:
			event_code = "ABS_HAT0X";
			break;
		case ABS_HAT0Y:
			event_code = "ABS_HAT0Y";
			break;
		case ABS_HAT1X:
			event_code = "ABS_HAT1X";
			break;
		case ABS_HAT1Y:
			event_code = "ABS_HAT1Y";
			break;
		case ABS_HAT2X:
			event_code = "ABS_HAT2X";
			break;
		case ABS_HAT2Y:
			event_code = "ABS_HAT2Y";
			break;
		case ABS_HAT3X:
			event_code = "ABS_HAT3X";
			break;
		case ABS_HAT3Y:
			event_code = "ABS_HAT3Y";
			break;
		case ABS_PRESSURE:
			event_code = "ABS_PRESSURE";
			break;
		case ABS_DISTANCE:
			event_code = "ABS_DISTANCE";
			break;
		case ABS_TILT_X:
			event_code = "ABS_TILT_X";
			break;
		case ABS_TILT_Y:
			event_code = "ABS_TILT_Y";
			break;
		case ABS_TOOL_WIDTH:
			event_code = "ABS_TOOL_WIDTH";
			break;
		case ABS_VOLUME:
			event_code = "ABS_VOLUME";
			break;
		case ABS_MISC:
			event_code = "ABS_MISC";
			break;
		case ABS_MT_SLOT:
			event_code = "ABS_MT_SLOT";
			break;
		case ABS_MT_TOUCH_MAJOR:
			event_code = "ABS_MT_TOUCH_MAJOR";
			break;
		case ABS_MT_TOUCH_MINOR:
			event_code = "ABS_MT_TOUCH_MINOR";
			break;
		case ABS_MT_WIDTH_MAJOR:
			event_code = "ABS_MT_WIDTH_MAJOR";
			break;
		case ABS_MT_WIDTH_MINOR:
			event_code = "ABS_MT_WIDTH_MINOR";
			break;
		case ABS_MT_ORIENTATION:
			event_code = "ABS_MT_ORIENTATION";
			break;
		case ABS_MT_POSITION_X:
			event_code = "ABS_MT_POSITION_X";
			break;
		case ABS_MT_POSITION_Y:
			event_code = "ABS_MT_POSITION_Y";
			break;
		case ABS_MT_TOOL_TYPE:
			event_code = "ABS_MT_TOOL_TYPE";
			break;
		case ABS_MT_BLOB_ID:
			event_code = "ABS_MT_BLOB_ID";
			break;
		case ABS_MT_TRACKING_ID:
			event_code = "ABS_MT_TRACKING_ID";
			break;
		case ABS_MT_PRESSURE:
			event_code = "ABS_MT_PRESSURE";
			break;
		case ABS_MAX:
			event_code = "ABS_MAX";
			break;
		default:
			sprintf(text, "EV_ABS[%d] = %d", event->code, event->value);
			return text;
		}
		break;

	case EV_MSC:
		sprintf(text, "EV_MSC[%d] = %d", event->code, event->value);
		return text;

	case EV_SW:
		sprintf(text, "EV_SW[%d] = %d", event->code, event->value);
		return text;

	case EV_LED:
		sprintf(text, "EV_LED[%d] = %d", event->code, event->value);
		return text;

	case EV_SND:
		sprintf(text, "EV_SND[%d] = %d", event->code, event->value);
		return text;

	case EV_REP:
		sprintf(text, "EV_REP[%d] = %d", event->code, event->value);
		return text;

	case EV_FF:
		sprintf(text, "EV_FF[%d] = %d", event->code, event->value);
		return text;

	case EV_PWR:
		sprintf(text, "EV_PWR[%d] = %d", event->code, event->value);
		return text;

	case EV_FF_STATUS:
		sprintf(text, "EV_FF_STATUS[%d] = %d", event->code, event->value);
		return text;

	default:
		return cavan_event_tostring_simple(event, text);
	}

	sprintf(text, "%s = %d", event_code, event->value);

	return text;
}

// ================================================================================

static void cavan_event_virtual_build_bitmask(struct single_link *link, uint8_t *bitmask)
{
	struct cavan_virtual_key *key;

	single_link_foreach(link, key)
	{
		set_bit(key->code, bitmask);
	}
	end_link_foreach(link);
}

static int cavan_event_parse_virtual_keymap(struct cavan_event_device *dev)
{
	size_t size;
	char pathname[1024];
	const char *mem, *p, *file_end;
	struct cavan_virtual_key *key;
	int x, y, width, height, code;

	sprintf(pathname, "/sys/board_properties/virtualkeys.%s", dev->name);
	mem = file_read_all(pathname, 0, &size);
	if (mem == NULL)
	{
		// pr_red_info("file_read_all %s", pathname);
		return -ENOMEM;
	}

	pr_bold_info("Parse virtual key file %s", pathname);

	file_end = mem + size;
	p = text_skip_space(mem, file_end);

	while (p < file_end)
	{
		if (text_lhcmp("0x01", p) || sscanf(p, "0x01:%d:%d:%d:%d:%d", &code, &x, &y, &width, &height) != 5)
		{
			p++;
			continue;
		}

		key = malloc(sizeof(*key));
		if (key == NULL)
		{
			pr_error_info("malloc");
			goto out_free_mem;
		}

		pr_bold_info("code = %d, x = %d, y = %d, width = %d, height = %d", code, x, y, width, height);

		width >>= 1;
		height >>= 1;

		key->left = x - width;
		key->right = x + width - 1;
		key->top = y - height;
		key->bottom = y + height - 1;
		key->code = code;
		key->value = 0;

		single_link_push(&dev->vk_link, &key->node);

		p = text_nfind2(p, file_end, ':', 5);
	}

out_free_mem:
	free((char *)mem);

	return 0;
}

static char *cavan_event_get_keylayout_pathname(struct cavan_event_device *dev, char *pathname)
{
	int i;
	char *filename;
	const char *filenames[] =
	{dev->name, "Generic", "qwerty"};

	filename = text_copy(pathname, "/system/usr/keylayout/");
	for (i = 0; i < (int)NELEM(filenames); i++)
	{
		sprintf(filename, "%s.kl", filenames[i]);
		if (access(pathname, R_OK) == 0)
		{
			return pathname;
		}
	}

	return NULL;
}

const char *cavan_event_find_key_name_base(struct single_link *link, int code)
{
	struct cavan_keylayout_node *key;

	single_link_foreach(link, key)
	{
		if (key->code == code)
		{
			link_foreach_return(link, key->name);
		}
	}

	end_link_foreach(link);

	return "NONE";
}

static void cavan_event_virtual_key_set_name(struct single_link *vk_link, struct single_link *kl_link)
{
	struct cavan_virtual_key *key;

	single_link_foreach(vk_link, key)
	{
		key->name = cavan_event_find_key_name_base(kl_link, key->code);
	}
	end_link_foreach(vk_link);
}

static int cavan_event_parse_keylayout(struct cavan_event_device *dev)
{
	int ret;
	char *mem;
	size_t size;
	char pathname[1024];
	uint8_t key_bitmask[KEY_BITMASK_SIZE];
	const char *p, *line_end, *file_end;
	struct cavan_keylayout_node *node;

	if (cavan_event_get_keylayout_pathname(dev, pathname) == NULL)
	{
		return -ENOENT;
	}

	memset(key_bitmask, 0, sizeof(key_bitmask));

	ret = ioctl(dev->fd, EVIOCGBIT(EV_KEY, sizeof(key_bitmask)), key_bitmask);
	if (ret < 0)
	{
		pr_error_info("ioctl EVIOCGBIT EV_KEY");
		return ret;
	}

	mem = file_read_all(pathname, 1, &size);
	if (mem == NULL)
	{
		pr_red_info("file_read_all %s", pathname);
		return -EFAULT;
	}

	mem[size] = 0;

	pr_bold_info("Parse keylayout file %s", pathname);

	p = mem;
	file_end = p + size;

	node = malloc(sizeof(*node));
	if (node == NULL)
	{
		pr_error_info("malloc");
		goto out_free_memory;
	}

	cavan_event_virtual_build_bitmask(&dev->vk_link, key_bitmask);

	while (p < file_end)
	{
		line_end = text_find_lf(p, file_end);
		if (line_end == NULL)
		{
			line_end = file_end;
		}

		p = text_skip_space(p, line_end);
		if (p == line_end || *p == '#')
		{
			goto label_goto_next_line;
		}

		ret = sscanf(p, "key %d %s", &node->code, node->name);
		if (ret != 2 || test_bit(node->code, key_bitmask) == 0)
		{
			goto label_goto_next_line;
		}

		pr_bold_info("name = %s, code = %d", node->name, node->code);

		single_link_push(&dev->kl_link, &node->node);

		node = malloc(sizeof(*node));
		if (node == NULL)
		{
			pr_error_info("malloc");
			goto label_goto_next_line;
		}

label_goto_next_line:
		p = text_skip_lf(line_end, file_end);
	}

	free(node);

	cavan_event_virtual_key_set_name(&dev->vk_link, &dev->kl_link);

out_free_memory:
	free(mem);

	return 0;
}

static void cavan_event_close_device_handler(struct double_link *link, struct double_link_node *node, void *data)
{
	struct cavan_event_service *service = data;
	struct cavan_event_device *dev = double_link_get_container(link, node);

	if (service->remove)
	{
		service->remove(dev, service->private_data);
	}

	close(dev->fd);

	single_link_free_all(&dev->kl_link);
	single_link_free_all(&dev->vk_link);

	free(dev);
}

static void cavan_event_close_devices(struct cavan_event_service *service)
{
	pthread_mutex_lock(&service->lock);
	double_link_destroy(&service->link, service, cavan_event_close_device_handler);
	pthread_mutex_unlock(&service->lock);
}

ssize_t cavan_event_scan_devices(struct cavan_event_matcher *matcher, void *data)
{
	int fd;
	int ret;
	DIR *dp;
	struct dirent *entry;
	char *filename;
	size_t count;

	if (matcher == NULL || matcher->handler == NULL)
	{
		pr_red_info("matcher == NULL || matcher->handler == NULL");
		return -EINVAL;
	}

	filename = text_copy(matcher->pathname, "/dev/input/");
	dp = opendir(matcher->pathname);
	if (dp == NULL)
	{
		pr_error_info("open directory `%s'", matcher->pathname);
		return -ENOENT;
	}

	count = 0;

	while ((entry = readdir(dp)))
	{
		if (text_lhcmp("event", entry->d_name))
		{
			continue;
		}

		pr_std_info("============================================================");

		text_copy(filename, entry->d_name);
		fd = open(matcher->pathname, O_RDONLY);
		if (fd < 0)
		{
			pr_error_info("open file `%s'", matcher->pathname);
			continue;
		}

		ret = cavan_event_get_devname(fd, matcher->devname, sizeof(matcher->devname));
		if (ret < 0)
		{
			pr_error_info("cavan_event_get_devname");
			close(fd);
			continue;
		}

		matcher->fd = fd;
		if (matcher->match && matcher->match(matcher, data) == false)
		{
			pr_red_info("Can't match device `%s', path = %s", matcher->devname, matcher->pathname);
			close(fd);
			continue;
		}

		ret = matcher->handler(matcher, data);
		if (ret < 0)
		{
			pr_red_info("Handler device `%s', path = %s", matcher->devname, matcher->pathname);
			close(fd);
			continue;
		}

		count++;
	}

	closedir(dp);

	return count;
}

static bool cavan_event_service_match(struct cavan_event_matcher *matcher, void *data)
{
	struct cavan_event_service *service = data;

	if (service->matcher)
	{
		return service->matcher(matcher, service->private_data);
	}

	return true;
}

static int cavan_event_service_match_handler(struct cavan_event_matcher *matcher, void *data)
{
	int ret;
	struct cavan_event_device *dev;
	struct cavan_event_service *service = data;

	dev = malloc(sizeof(*dev));
	if (dev == NULL)
	{
		pr_error_info("malloc");
		return -ENOMEM;
	}

	ret = single_link_init(&dev->vk_link, MOFS(struct cavan_virtual_key, node));
	if (ret < 0)
	{
		pr_red_info("single_link_init");
		goto out_free_dev;
	}

	ret = single_link_init(&dev->kl_link, MOFS(struct cavan_keylayout_node, node));
	if (ret < 0)
	{
		pr_red_info("single_link_init");
		goto out_single_link_deinit_vk;
	}

	dev->fd = matcher->fd;
	text_ncopy(dev->name, matcher->devname, sizeof(dev->name));
	text_ncopy(dev->pathname, matcher->pathname, sizeof(dev->pathname));

	if (service->probe && service->probe(dev, service->private_data) < 0)
	{
		ret = -EFAULT;
		pr_red_info("Faile to probe device %s, name = %s", matcher->pathname, matcher->devname);
		goto out_single_link_deinit_kl;
	}

	pr_green_info("Add device %s, name = %s", matcher->pathname, matcher->devname);

	cavan_event_parse_virtual_keymap(dev);
	cavan_event_parse_keylayout(dev);

	double_link_append(&service->link, &dev->node);

	return 0;

out_single_link_deinit_kl:
	single_link_deinit(&dev->kl_link);
out_single_link_deinit_vk:
	single_link_deinit(&dev->vk_link);
out_free_dev:
	free(dev);
	return ret;
}

static int cavan_event_open_devices(struct cavan_event_service *service)
{
	ssize_t count;
	struct cavan_event_matcher matcher =
	{
		.match = cavan_event_service_match,
		.handler = cavan_event_service_match_handler
	};

	count = cavan_event_scan_devices(&matcher, service);
	if (count < 0)
	{
		pr_red_info("cavan_event_scan_devices");
	}

	return count;
}

static int cavan_event_service_handler(struct cavan_thread *thread, void *data)
{
	int ret;
	ssize_t rdlen;
	struct cavan_event_service *service = data;
	struct pollfd *pfds = service->pfds;
	struct cavan_event_device *pdev;
	struct double_link *link;
	struct double_link_node *node, *head;
	struct input_event events[32], *ep, *ep_end;

	ret = poll(pfds, service->pfd_count, -1);
	if (ret < 0)
	{
		pr_error_info("poll");
		return ret;
	}

	if (pfds[0].revents)
	{
		return 0;
	}

	link = &service->link;

	pthread_mutex_lock(&link->lock);

	for (head = &link->head_node, node = head->next; node != head; node = node->next)
	{
		pdev = double_link_get_container(link, node);
		if (pdev->pfd->revents == 0)
		{
			continue;
		}

		rdlen = read(pdev->fd, events, sizeof(events));
		if (rdlen < 0)
		{
			pr_error_info("read");
			pthread_mutex_unlock(&link->lock);
			return rdlen;
		}

		for (ep = events, ep_end = ep + (rdlen / sizeof(events[0])); ep < ep_end; ep++)
		{
			if (service->event_handler(pdev, ep, service->private_data) == false)
			{
				char print_buff[1024];

				pr_red_info("%s", cavan_event_tostring(ep, print_buff));
			}
		}
	}

	pthread_mutex_unlock(&link->lock);

	return 0;
}

struct cavan_virtual_key *cavan_event_find_virtual_key(struct cavan_event_device *dev, int x, int y)
{
	struct cavan_virtual_key *key;

	single_link_foreach(&dev->vk_link, key)
	{
		if (y >= key->top && y <= key->bottom && x >= key->left && x <= key->right)
		{
			link_foreach_return(&dev->vk_link, key);
		}
	}
	end_link_foreach(&dev->vk_link);

	return NULL;
}

void cavan_event_service_init(struct cavan_event_service *service, bool (*matcher)(struct cavan_event_matcher *, void *))
{
	service->matcher = matcher;
	service->probe = NULL;
	service->remove = NULL;
	service->event_handler = NULL;
}

static bool cavan_event_handler_dummy(struct cavan_event_device *dev, struct input_event *event, void *data)
{
	char buff[1024];

	print_string(cavan_event_tostring(event, buff));

	return true;
}

int cavan_event_service_start(struct cavan_event_service *service, void *data)
{
	int ret;
	ssize_t count;
	struct double_link *link;
	struct double_link_node *node;
	struct cavan_event_device *dev;
	struct pollfd *pfd, *pfd_end;
	struct cavan_thread *thread;

	if (service == NULL)
	{
		pr_red_info("service == NULL");
		return -EINVAL;
	}

	if (service->event_handler == NULL)
	{
		service->event_handler = cavan_event_handler_dummy;
	}

	service->private_data = data;
	pthread_mutex_init(&service->lock, NULL);

	ret = double_link_init(&service->link, MOFS(struct cavan_event_device, node));
	if (ret < 0)
	{
		pr_red_info("double_link_init");
		return ret;
	}

	count = cavan_event_open_devices(service);
	if (count < 0)
	{
		ret = count;
		pr_red_info("cavan_event_open_devices");
		goto out_double_link_deinit;
	}

	if (count == 0)
	{
		ret = -ENOENT;
		pr_red_info("No input device found!");
		goto out_double_link_deinit;
	}

	thread = &service->thread;
	thread->name = "EVENT";
	thread->wake_handker = NULL;
	thread->handler = cavan_event_service_handler;
	ret = cavan_thread_init(thread, service);
	if (ret < 0)
	{
		pr_red_info("cavan_thread_init");
		goto out_cavan_event_close_devices;
	}

	service->pfd_count = count + 1;
	pfd = malloc(service->pfd_count * sizeof(*pfd));
	if (pfd == NULL)
	{
		ret = -ENOMEM;
		pr_error_info("malloc");
		goto out_cavan_thread_deinit;
	}

	service->pfds = pfd;

	*pfd = service->thread.pfd;
	link = &service->link;

	pthread_mutex_lock(&link->lock);

	for (pfd++, pfd_end = pfd + count, node = link->head_node.next; pfd < pfd_end; pfd++, node = node->next)
	{
		dev = double_link_get_container(link, node);

		dev->pfd = pfd;
		pfd->fd = dev->fd;
		pfd->events = POLLIN;
		pfd->revents = 0;
	}

	pthread_mutex_unlock(&link->lock);

	ret = cavan_event_start_poll_thread(service);
	if (ret < 0)
	{
		pr_red_info("cavan_event_start_poll_thread");
		goto out_free_pfd;
	}

	return 0;

out_free_pfd:
	free(pfd);
out_cavan_thread_deinit:
	cavan_thread_deinit(thread);
out_cavan_event_close_devices:
	cavan_event_close_devices(service);
out_double_link_deinit:
	double_link_deinit(&service->link);
	return ret;
}

void cavan_event_service_stop(struct cavan_event_service *service)
{
	cavan_event_stop_poll_thread(service);
	free(service->pfds);
	cavan_event_close_devices(service);
	cavan_thread_deinit(&service->thread);
	pthread_mutex_destroy(&service->lock);
}

bool cavan_event_simple_matcher(struct cavan_event_matcher *matcher, void *data)
{
	if (data)
	{
		return text_cmp(matcher->devname, data) == 0 || text_cmp(matcher->pathname, data) == 0;
	}

	return true;
}

bool cavan_event_name_matcher(const char *devname, ...)
{
	va_list ap;
	const char *name;

	va_start(ap, devname);

	while (1)
	{
		name = va_arg(ap, const char *);
		if (name == NULL)
		{
			break;
		}

		if (strcmp(devname, name) == 0)
		{
			break;
		}
	}

	va_end(ap);

	return name ? true : false;
}

int cavan_event_get_absinfo(int fd, int axis, int *min, int *max)
{
	int ret;
	struct input_absinfo info;

	ret = ioctl(fd, EVIOCGABS(axis), &info);
	if (ret < 0)
	{
		pr_error_info("ioctl EVIOCGABS");
		return ret;
	}

	*min = info.minimum;
	*max = info.maximum;

	return 0;
}
