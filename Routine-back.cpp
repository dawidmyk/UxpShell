auto now_end = it;
	it = begin;
	while(it != now_end) {
		(*it)->join();
		it++;
	}
	return i;
