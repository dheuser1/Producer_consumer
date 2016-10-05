#ifndef BUFFER_H
#define BUFFER_H
class buffer
{
	public:
	buffer();
	int insert_item(int item);
	int remove_item();
	
	private:
	int element_num;
	int enter_point;
	int exit_point;
	int data[5];
	
};
#endif // BUFFER_H
