#pragma once

class Keydown_Handler
{
public:
	virtual void on_keydown(int key, bool is_special) = 0;
};