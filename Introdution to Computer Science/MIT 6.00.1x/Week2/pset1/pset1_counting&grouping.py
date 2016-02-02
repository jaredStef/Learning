def item_order(order):
	salads     = str(order.count('salad'))
	waters     = str(order.count('water'))
	hamburgers = str(order.count('hamburger'))
	return "salad:" + salads + " hamburger:" + hamburgers + " water:" + waters

print item_order(order)
