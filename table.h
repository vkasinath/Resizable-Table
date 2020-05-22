//create a table.h class

template <class T> 
class Table{
	
private:
	//CLASS REPRESENTATIONS
	unsigned int row, col;
	T** values = NULL;

public:

	//CLASS CONSTRUCTORS, ASSIGNMENT, AND DESTRUCTOR
	Table(unsigned int row, unsigned int col, const T& v);
 	Table(const Table &t);
 	~Table();
 	Table& operator=(const Table &t);

 	//CLASS MEMBER FUNCTIONS AND OTHER OPERATORS
 	void print();

	T get(const unsigned int i, const unsigned int j);											//get cell value for [i][j]
	unsigned int numRows() const{return row;}													//returns number of table rows
	unsigned int numColumns() const{return col;}												//returns number of table columns
	void set(const unsigned int i, const unsigned int j, const T &v);							//set [i][j] cell value

	void push_back_row(const std::vector <T> &t);												//add a row at the end of a table
	void push_back_rows(const Table &t);														//add mutiple rows at the end of a table
	void pop_back_row();																		//delete the last row in a table

	void push_back_column(const std::vector <T> &t);											//add a column at the end of all rows
	void push_back_columns(const Table &t);														//add multiple columns at the end of rows		
	void pop_back_column();																		//delete the last column in every row

	//UTILITY FUNCTIONS
	void cleanup();																				//cleanup all pointer of pointer values
	void copy_values_to_temp(T** temp, const std::string &action);								//move values to a temp point of pointers
	void push_back_1rc(const std::vector <T> &t);												//special case for 1row 1col push_back

};

//constructor
template <class T> Table<T>::Table(unsigned int row, unsigned int col, const T& v){
	this->row = row;
	this->col = col;
	values = new T* [row];
	for (unsigned int i = 0; i < row; i++){
		values[i] = new T [col];
		for (unsigned int j = 0; j < col; j++) values[i][j] = v;
	}
}

//copy constructor
template <class T> Table<T>::Table(const Table &t){
	row = t.row;
	col = t.col;

	this->values = new T* [row];
	for (unsigned int i = 0; i < row; i++){
		this->values[i] = new T [col];
		for (unsigned int j = 0; j < col; j++) this->values[i][j] = t.values[i][j];
	}
}

//destructor function
template <class T> Table<T>::~Table(){
	cleanup();
	row = 0;
	col = 0;
}

//print function
template <class T> void Table<T>::print(){
	std::cout << "table: " << row << " rows, " << col << " cols" << std::endl;

	for (unsigned int i = 0; i < row; i++){
		for (unsigned int j = 0; j < col; j++)
			std::cout << values[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <class T> T Table<T>::get(const unsigned int i, const unsigned int j){
	if (i < row && j < col && i >= 0 && j >= 0)
		return values[i][j];
	else{
		std::cerr << "in get function: incorrect row/column parameters given" << std::endl;
		exit(1);
	}
}

template <class T> void Table<T>::set(const unsigned int i, const unsigned int j, const T &v){
	if (i < row && j < col && i >= 0 && j >= 0)
		values[i][j] = v;
	else{
		std::cerr << "in set function: incorrect row/column parameters given" << std::endl;
		exit(1);
	}
}

template <class T> void Table<T>::push_back_row(const std::vector <T> &t){
	if (col == 0)
		push_back_1rc(t);
	else{
		if (t.size() == col){
			T** temp = new T* [row+1];
			
			copy_values_to_temp(temp, "push_back_row");

			temp[row] = new T [col];								// create an extra row from the vector provided
			for (unsigned int j = 0; j < col; j++)
				temp[row][j] = t[j];

			cleanup();
			values = temp;
			row++;
		}
		else{
			std::cerr << "in push_back_row function: incorrect vector size" << std::endl;
			exit(1);
		}
	}
}	

template <class T> void Table<T>::push_back_rows(const Table &t){
	std::vector<T> v;
	for (unsigned int i = 0; i < t.row; i++){						// sit in a loop, creating a vector for each row in the input table
		for (unsigned int j = 0; j < t.col; j++)
			v.push_back(t.values[i][j]);
		push_back_row(v);
		v.clear();
	}
}

template <class T> void Table<T>::pop_back_row(){
	if (row > 0){
		T** temp = new T* [row-1];

		copy_values_to_temp(temp, "pop_back_row");

		cleanup();
		values = temp;
		row--;
		if (row == 0) col = 0;
	}
	else{
		std::cerr << "in pop_back_row function: no rows to delete" << std::endl;
		exit(1);
	}
}

template <class T> void Table<T>::push_back_column(const std::vector <T> &t){
	if (row == 0)
		push_back_1rc(t);
	else{
		if (t.size() == row){
			T** temp = new T* [row];

			copy_values_to_temp(temp, "push_back_column");
		
			for (unsigned int i = 0; i < row; i++) temp[i][col] = t[i];				//add the values from the vector to the end of each row

			cleanup();
			values = temp;
			col++;
		}
		else{
			std::cerr << "in push_back_column function: incorrect vector size" << std::endl;
			exit(1);
		}
	}
}

template <class T> void Table<T>::push_back_columns(const Table &t){
	std::vector<T> v;
	for (unsigned int j = 0; j < t.col; j++){										//loop creating a vector for each row in the input table
		for (unsigned int i = 0; i < t.row; i++)
			v.push_back(t.values[i][j]);
		push_back_column(v);
		v.clear();
	}
}

template <class T> void Table<T>::pop_back_column(){
	if (col > 0){
		T** temp = new T* [row];

		copy_values_to_temp(temp, "pop_back_column");

		cleanup();
		values = temp;
		col--;

		if (col == 0) row = 0;

	}
	else{
		std::cerr << "in pop_back_column function: no columns to delete" << std::endl;
		exit(1);
	}
}

template <class T> void Table<T>::cleanup(){
	for (unsigned int i = 0; i < row; i++) delete[] values[i];
		delete[] values;

}

template <class T> void Table<T>::copy_values_to_temp(T** temp, const std::string &action){
	unsigned int lr, lc, c;
	if (action == "push_back_row"){
		lr = row;
		lc = col;
		c = col;
	}
	else if (action == "pop_back_row"){
		lr = row-1;
		lc = col;
		c = col;
	}
	else if (action == "push_back_column"){
		lr = row;
		lc = col;
		c = col+1;
	}
	else if (action == "pop_back_column"){
		lr = row;
		lc = col-1;
		c = col-1;
	}

	for (unsigned int i = 0; i < lr; i++){
		temp[i] = new T [c];
		for (unsigned int j = 0; j < lc; j++)
			temp[i][j] = values[i][j];
	}	

}

template <class T> Table<T>& Table<T>::operator=(const Table &t){
	if (this == &t)
		return *this;

	cleanup();

	this->row = t.row;
	this->col = t.col;
	this->values = new T* [t.row];

	for (unsigned int i = 0; i < t.row; i++){
		this->values[i] = new T[t.col];
		for (unsigned int j = 0; j < t.col; j++) this->values[i][j] = t.values[i][j];
	}

	return *this;

}

//special function to handle one row and one column situations
template <class T> void Table<T>::push_back_1rc(const std::vector <T> &t){
	if (t.size() != 1){
		std::cerr << "in push_back_1rc function: vector size should be 1" << std::endl;
		exit(1);
	}
	T** temp = new T*[1];
	temp[0] = new T[1];

	temp[0][0] = t[0];

	cleanup();
	values = temp;
	row = 1;
	col = 1;
}