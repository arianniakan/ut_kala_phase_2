
char** getinput();

struct User* signup(char** input);

int command_check(char** input);


int check_signup(char** input, struct User* users, int num_of_users);
int login(char** input, struct User* users, int num_of_users, int* user_num);
void logout(int* loged_in);
int seller_command_check(char** input);
int buyer_command_check(char** input);

void view_user(struct User loged_in_user);
void deposit(struct User* loged_in_user, char** input);
struct Product* add_goods(char** input, struct User* loged_in_user);
int check_add_goods(char** input, struct Product* products, int num_of_products, struct User* loged_in_user);
void show_goods(struct Product* products, int num_of_goods);
int buy(char** input, struct Product* products, int num_of_products, struct User* loged_in_user, struct User* users, int num_of_users);
int check_buy(char** input, struct Product* products, int num_of_products, struct User* users, int num_of_users, struct User loged_in_user);

char** split(char* input);
char* readFile(FILE* file);
char* readline(int line_number, char* str);
struct User* read_user(char** line_user);
void write_all_data(int num_of_bought_products, int num_of_users, int num_of_products, struct User* users, struct Product* products);
struct Product* read_products(char** input);

int remove_good(struct Product* products, char** input, struct User* loged_in_user);
int remove_good_user(char** input, struct User* loged_in_user);
int change_goods_price(struct User* loged_in_user, struct Product* products, char** input, int num_of_products);
int rate_goods(struct Product* products, struct User* users, int num_of_users, int num_of_products, struct User* loged_in_user, char** input);

void mergeSort(struct Product** source);

void search(char** input, struct Product* products, int num_of_products);

