
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
struct Product
{
    struct User* seller;
    char* name;
    int price;
    int count;
    char* rating;
    int num_of_ratings;
    struct Product* next;

};
struct User
{
    char* name;
    char* password;
    char* role;
    int deposit;
    int products_num;
    struct Product* products;
    struct User* next;
};


void partition(struct Product* head, struct Product** front, struct Product** back) {

    struct Product* fast;
    struct Product* slow;

    if (head == NULL || head->next == NULL) {

        *front = head; // &a
        *back = NULL; // &b

    }
    else {

        slow = head;
        fast = head->next;

        while (fast != NULL) {

            fast = fast->next;

            if (fast != NULL) {

                slow = slow->next;
                fast = fast->next;

            }

        }

        *front = head; // a
        *back = slow->next; // b
        slow->next = NULL;


    }

}

struct Product* mergeLists(struct Product* a, struct Product* b) {

    struct Product* mergedList = NULL;

    if (a == NULL) {
        return b;
    }
    else if (b == NULL) {
        return a;
    }

    if (strcmp(a->name, b->name) < 0) {
        mergedList = a;
        mergedList->next = mergeLists(a->next, b);
    }
    else {
        mergedList = b;
        mergedList->next = mergeLists(a, b->next);
    }

    return mergedList;

}

void mergeSort(struct Product** source) {

    struct Product* head = *source;
    struct Product* a = NULL;
    struct Product* b = NULL;

    if (head == NULL || head->next == NULL) {

        return;

    }

    partition(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *source = mergeLists(a, b);

}





char* readFile(FILE* file)
{

    char* code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL;

    code = malloc(n + 1);

    while (1 == 1)
    {
        if ((c = fgetc(file)) != EOF)
        {
            code[n++] = (char)c;
            code = realloc(code, n + 1);
        }
        else if ((c = fgetc(file)) == EOF)
        {
            break;
        }

    }

    code[n] = '\0';

    return code;
}
char* getinput()
{
    char* str;
    int i = 0;
    char key = 0;
    str = malloc(sizeof(char));
    while (key != '\n')
    {
        key = getchar();
        if (key == '\n')
        {
            str[i] = 0;
            i++;
            str = realloc(str, (i + 1) * sizeof(char));
        }
        str[i] = key;
        i++;
        str = realloc(str, (i + 1) * sizeof(char));

    }




    return str;
}

char** split(char* input)
{
    char** list;
    list = malloc(sizeof(char*));
    list[0] = malloc(1 * sizeof(char));
    int i = 0;
    int j = 0;
    int k = 0;
    while (1 == 1)
    {

        while (1 == 1)
        {
            if (input[k] == ' ')
            {
                k += 1;
            }
            list[i][j] = input[k];
            k += 1;
            if (input[k] == 0)
            {
                break;
            }


            if (input[k] == ' ')
            {
                j += 1;
                list[i] = realloc(list[i], (j + 1) * sizeof(char));

                break;
            }
            j += 1;
            list[i] = realloc(list[i], (j + 1) * sizeof(char));
        }
        if (input[k] == 0)
        {
            j += 1;
            list[i][j] = 0;
            i += 1;
            list = realloc(list, (i + 1) * sizeof(char*));
            list[i] = malloc(sizeof(char));
            list[i][0] = 0;


            break;
        }
        list[i][j] = 0;
        i += 1;
        j = 0;
        list = realloc(list, (i + 1) * sizeof(char*));
        list[i] = malloc(sizeof(char));
    }

    return list;
}




int command_check(char** input)
{
    if (strcmp(input[0], "signup") == 0 || strcmp(input[0], "SIGNUP") == 0 || strcmp(input[0], "Signup") == 0)
    {
        return 1;
    }
    if (strcmp(input[0], "login") == 0 || strcmp(input[0], "LOGIN") == 0 || strcmp(input[0], "Login") == 0)
    {
        return 2;
    }
    if (strcmp(input[0], "show_goods") == 0 || strcmp(input[0], "SHOW_GOODS") == 0 || strcmp(input[0], "Show_Goods") == 0 || strcmp(input[0], "Show_goods") == 0)
    {
        return 3;
    }
    else
    {
        printf("invalid command try again!\n");
    }
}

int check_signup(char** input, struct User* users, int num_of_users)
{
    struct User* curr = users;
    for (int i = 0;i < 4;i++)
    {
        if (strcmp(input[i], "") == 0)
        {
            printf("invalid input for sign up\n");
            return 0;
        }
    }
    int i = 0;
    while (1 == 1)
    {
        if (i == num_of_users)
        {
            curr = users;
            break;
        }

        if (strcmp(input[1], curr->name) == 0 && strcmp(input[3], curr->role) == 0)
        {

            printf("that user is already taken!\n");
            return 0;
        }
        curr = curr->next;
        i++;
    }

    if (strcmp(input[3], "Seller") != 0 && strcmp(input[3], "SELLER") != 0 && strcmp(input[3], "seller") != 0 && strcmp(input[3], "buyer") != 0 && strcmp(input[3], "Buyer") != 0 && strcmp(input[3], "BUYER") != 0)
    {
        printf("Enter a valide Role!\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

struct User* signup(char** input)
{

    struct User* new_user;
    new_user = malloc(1 * sizeof(struct User));
    new_user->name = input[1];
    new_user->password = input[2];
    if (strcmp(input[3], "seller") == 0 || strcmp(input[3], "Seller") == 0 || strcmp(input[3], "SELLER") == 0)
    {
        new_user->role = "seller";
    }
    else
    {
        new_user->role = "buyer";
    }
    new_user->next = NULL;

    new_user->products = malloc(sizeof(struct Product));
    new_user->products = 0;
    new_user->deposit = 0;
    new_user->products_num = 0;
    printf("you have successfully been signed in as %s\n", new_user->name);


    return new_user;



}

int login(char** input, struct User* users, int num_of_users, int* user_num)
{
    struct User* curr = users;
    for (int i = 0;i < 4;i++)
    {
        if (strcmp(input[i], "") == 0)
        {
            printf("invalid input for login\n");
            return 0;
        }
    }
    for (int i = 0;i < num_of_users;i++)
    {
        if (strcmp(curr->password, input[2]) == 0 && strcmp(curr->role, input[3]) == 0 && strcmp(curr->name, input[1]) == 0)
        {
            if (strcmp(input[3], "seller") == 0)
            {
                printf("Welcome %s\nYou have been loged in as a %s\n", input[1], input[3]);
                *user_num = i;
                return 1;
            }
            else if (strcmp(input[3], "buyer") == 0)
            {
                printf("Welcome %s\nYou have been loged in as a %s\n", input[1], input[3]);
                *user_num = i;
                return 2;
            }

        }
        else if (strcmp(curr->name, input[1]) == 0)
        {
            if (strcmp(curr->password, input[2]) != 0)
            {
                printf("invalid password\n");
                return 0;
            }

        }
        curr = curr->next;

    }
    printf("This user does not exist!\n");
    return 0;



}


int seller_command_check(char** input)
{
    if (strcmp(input[0], "logout") == 0 || strcmp(input[0], "LOGOUT") == 0 || strcmp(input[0], "Logout") == 0)
    {
        return 1;
    }
    if (strcmp(input[0], "view") == 0 || strcmp(input[0], "VIEW") == 0 || strcmp(input[0], "View") == 0)
    {
        return 2;
    }
    if (strcmp(input[0], "add_goods") == 0 || strcmp(input[0], "Add_goods") == 0 || strcmp(input[0], "ADD_GOODS") == 0 || strcmp(input[0], "Add_Goods") == 0)
    {
        return 3;
    }
    if (strcmp(input[0], "show_goods") == 0 || strcmp(input[0], "SHOW_GOODS") == 0 || strcmp(input[0], "Show_Goods") == 0 || strcmp(input[0], "Show_goods") == 0)
    {
        return 4;
    }
    if (strcmp(input[0], "remove_goods") == 0 || strcmp(input[0], "REMOVE_GOODS") == 0 || strcmp(input[0], "Remove_Goods") == 0 || strcmp(input[0], "Remove_goods") == 0)
    {
        return 5;
    }
    if (strcmp(input[0], "change_goods_price") == 0 || strcmp(input[0], "Change_goods_price") == 0 || strcmp(input[0], "Change_Goods_Price") == 0 || strcmp(input[0], "CHANGE_GOODS_PRICE") == 0)
    {
        return 6;
    }
    if (strcmp(input[0], "search") == 0)
    {
        return 7;
    }
    else
    {
        printf("invalid command try again!\n");
    }
}
int buyer_command_check(char** input)
{
    if (strcmp(input[0], "logout") == 0 || strcmp(input[0], "LOGOUT") == 0 || strcmp(input[0], "Logout") == 0)
    {
        return 1;
    }
    if (strcmp(input[0], "view") == 0 || strcmp(input[0], "VIEW") == 0 || strcmp(input[0], "View") == 0)
    {
        return 2;
    }
    if (strcmp(input[0], "deposit") == 0 || strcmp(input[0], "DEPOSIT") == 0 || strcmp(input[0], "Deposit") == 0)
    {
        if (input[1][0] == 0)
        {
            printf("you must enter a number to add to your account!\ntry again!\n");
            return 0;

        }
        int i = 0;
        while (1 == 1)
        {
            if (input[1][i] == 0 && i != 0)
            {
                return 3;
            }
            else if (input[1][i] != '1' && input[1][i] != '2' && input[1][i] != '3' && input[1][i] != '4' && input[1][i] != '5' && input[1][i] != '6' && input[1][i] != '7' && input[1][i] != '8' && input[1][i] != '9' && input[1][i] != '0')
            {
                printf("thats an invalid value to deposit(it must be a number)\n");
                return 0;
            }


            i++;

        }

    }
    if (strcmp(input[0], "show_goods") == 0 || strcmp(input[0], "SHOW_GOODS") == 0 || strcmp(input[0], "Show_Goods") == 0 || strcmp(input[0], "Show_goods") == 0)
    {
        return 4;
    }
    if (strcmp(input[0], "buy") == 0 || strcmp(input[0], "BUY") == 0 || strcmp(input[0], "Buy") == 0)
    {
        return 5;
    }
    if (strcmp(input[0], "rate_goods") == 0 || strcmp(input[0], "Rate_Goods") == 0 || strcmp(input[0], "RATING_GOODS") == 0 || strcmp(input[0], "RATING_GOODS") == 0 || strcmp(input[0], "Rating_goods") == 0)
    {
        return 6;
    }
    if (strcmp(input[0], "search") == 0)
    {
        return 7;
    }
    else
    {
        printf("invalid command try again!\n");
    }
}
void logout(int* loged_in)
{
    *loged_in = 0;
    printf("logout successful!\n");
}
void view_user(struct User loged_in_user)
{
    struct Product* current_product = loged_in_user.products;
    int i = 0;
    printf("\nUserName: %s", loged_in_user.name);
    printf("\nRole: %s\n", loged_in_user.role);
    if (strcmp(loged_in_user.role, "seller") == 0)
    {
        printf("the products you are selling are: ");

        while (1 == 1)
        {
            if (loged_in_user.products == 0)
            {
                printf("(this user is not selling any products yet!)\n");
                break;
            }
            if (i == loged_in_user.products_num)
            {
                printf("\n");
                break;
            }
            if (current_product->num_of_ratings < 5 || atof(current_product->rating) > 2)
            {
                printf("\nname: %s", current_product->name);
                printf("    price: %d", current_product->price);
                printf("    count: %d", current_product->count);
                printf("    rating: %s", current_product->rating);
            }
            if (current_product->num_of_ratings > 4 && atof(current_product->rating) < 2)
            {
                printf("\nname: %s", current_product->name);
                printf("    price: %d", current_product->price);
                printf("    count: %d", current_product->count);
                printf("    rating: %s", current_product->rating);
                printf("    ((disabled due to bad rating.))\n");
            }

            current_product = current_product->next;
            i++;
        }

    }

    if (strcmp(loged_in_user.role, "buyer") == 0)
    {
        printf("Deposit: %d\n", loged_in_user.deposit);

        printf("the products you are buying are: ");

        while (1 == 1)
        {
            if (loged_in_user.products == 0)
            {
                printf("(this user is not buying any products yet!)\n");
                break;
            }
            if (current_product == 0)
            {
                printf("\n");
                break;
            }
            printf("\nname: %s", current_product->name);
            printf("    price: %d", current_product->price);
            printf("    count: %d", current_product->count);
            printf("    rating: %s", current_product->rating);
            printf("    seller: %s", current_product->seller->name);
            current_product = current_product->next;
            i++;
        }

    }

}
void deposit(struct User* loged_in_user, char** input)
{
    loged_in_user->deposit += atoi((input[1]));
    printf("%s has been added to your account\n", input[1]);
}
struct Product* add_goods(char** input, struct User* loged_in_user)
{

    struct Product* new_product;
    new_product = malloc(sizeof(struct Product));
    new_product->name = input[1];
    new_product->price = atoi(input[2]);
    new_product->count = atoi(input[3]);
    new_product->rating = "(no_rating)";
    new_product->seller = loged_in_user;
    new_product->num_of_ratings = 0;
    loged_in_user->products_num += 1;
    new_product->next = loged_in_user->products;
    loged_in_user->products = new_product;
    new_product->next = NULL;

    return new_product;
}
int check_add_goods(char** input, struct Product* products, int num_of_products, struct User* loged_in_user)
{
    struct Product* curr_product = products;
    struct Product* curr_user_product = loged_in_user->products;
    if (num_of_products > 0)
    {
        for (int i = 0; i < num_of_products; i++)
        {
            if (strcmp(curr_product->name, input[1]) == 0 && strcmp(curr_product->seller->name, loged_in_user->name) != 0)
            {
                printf("this item is already being sold by %s.\n", curr_product->seller->name);
                return 0;
            }
            else if (strcmp(curr_product->name, input[1]) == 0 && strcmp(curr_product->seller->name, loged_in_user->name) == 0 && curr_product->price != atoi(input[2]))
            {

                printf("to change the price of a product use the command change_goods_price\n");
                return 0;


            }
            else if (strcmp(curr_product->name, input[1]) == 0 && strcmp(curr_product->seller->name, loged_in_user->name) == 0 && curr_product->price == atoi(input[2]))
            {
                for (int j = 0; j < loged_in_user->products_num;j++)
                {
                    if (strcmp(curr_user_product->name, curr_product->name) == 0)
                    {
                        break;
                    }
                    curr_user_product = curr_user_product->next;
                }
                curr_user_product->count += atoi(input[3]);
                curr_product->count += atoi(input[3]);
                printf("%s added to your count of %ss\n", input[3], input[1]);

                return 0;


            }
            curr_product = curr_product->next;
        }
    }
    int i = 0;
    for (int i = 0;i < 4;i++)
    {
        if (strcmp(input[i], "") == 0)
        {
            printf("invalid input to add a good\n");
            return 0;
        }
    }
    while (1 == 1)
    {
        if (input[2][i] == 0 && i != 0)
        {
            break;
        }
        else if (input[2][i] != '1' && input[2][i] != '2' && input[2][i] != '3' && input[2][i] != '4' && input[2][i] != '5' && input[2][i] != '6' && input[2][i] != '7' && input[2][i] != '8' && input[2][i] != '9' && input[2][i] != '0')
        {
            printf("thats an invalid value for price(it must be a number)\n");
            return 0;
        }


        i++;

    }
    i = 0;
    while (1 == 1)
    {
        if (input[3][i] == 0 && i != 0)
        {
            break;
        }
        else if (input[3][i] != '1' && input[3][i] != '2' && input[3][i] != '3' && input[3][i] != '4' && input[3][i] != '5' && input[3][i] != '6' && input[3][i] != '7' && input[3][i] != '8' && input[3][i] != '9' && input[3][i] != '0')
        {
            printf("thats an invalid value for count(it must be a number)\n");
            return 0;
        }


        i++;

    }
    return 1;

}
void show_goods(struct Product* products, int num_of_goods)
{
    int i = 0;
    struct Product* curr_product = products;
    while (1 == 1)
    {
        if (num_of_goods == 0)
        {
            printf("there's nothing go away");
            printf("\n");
            break;
        }
        if (i == num_of_goods)
        {
            printf("\n");
            break;
        }
        if (curr_product->num_of_ratings < 5 || atof(curr_product->rating) > 2)
        {
            printf("\nname: %s", curr_product->name);
            printf("    price: %d", curr_product->price);
            printf("    count: %d", curr_product->count);
            printf("    rating: %s", curr_product->rating);
            printf("    seller: %s\n", curr_product->seller->name);
        }


        curr_product = curr_product->next;
        i++;
    }
}
int buy(char** input, struct Product* products, int num_of_products, struct User* loged_in_user, struct User* users, int num_of_users)
{
    struct Product* new_product = malloc(sizeof(struct Product));
    struct Product* bought_product = products;
    struct User* seller = users;
    struct Product* user_products = loged_in_user->products;


    int i = 0;
    int j = 0;
    int k = 0;
    int a = 0;

    while (1 == 1)
    {
        if (strcmp(input[3], seller->name) == 0 && strcmp(seller->role, "seller") == 0)
        {
            break;
        }
        seller = seller->next;
        i++;
    }

    while (1 == 1)
    {
        if (strcmp(input[1], bought_product->name) == 0)
        {
            break;
        }
        bought_product = bought_product->next;
        j++;
    }
    while (a != loged_in_user->products_num)
    {
        if (strcmp(input[1], user_products->name) == 0)
        {
            user_products->count += atoi(input[2]);
            loged_in_user->deposit -= atoi(input[2]) * bought_product->price;
            bought_product->count -= atoi(input[2]);
            return 0;

        }
        user_products = user_products->next;
        a++;


    }
    new_product->count = 0;
    new_product->name = input[1];
    new_product->count += atoi(input[2]);
    loged_in_user->products_num += 1;
    new_product->price = bought_product->price;
    new_product->num_of_ratings = 0;
    new_product->rating = "(you_have_not_rated_this_product_yet)";
    new_product->seller = seller;
    new_product->next = loged_in_user->products;
    loged_in_user->products = new_product;
    loged_in_user->deposit -= atoi(input[2]) * bought_product->price;

    bought_product->count -= atoi(input[2]);

    return 1;



}
int check_buy(char** input, struct Product* products, int num_of_products, struct User* users, int num_of_users, struct User loged_in_user)
{
    struct User* seller = users;
    struct Product* thing;
    struct Product* in_products = products;
    int i = 0;
    int j = 0;
    int k = 0;


    for (int i = 0;i < 4;i++)
    {
        if (strcmp(input[i], "") == 0)
        {
            printf("invalid input\n");
            return 0;
        }
    }
    while (1 == 1)
    {
        if (strcmp(input[3], seller->name) == 0 && strcmp(seller->role, "seller") == 0)
        {
            break;
        }
        if (i == num_of_users - 1)
        {
            printf("a user with that name is not selling that product!\n");
            return 0;
        }
        seller = seller->next;

        i++;
    }
    thing = seller->products;
    while (1 == 1)
    {

        if (strcmp(input[1], thing->name) == 0)
        {
            break;
        }
        else if (k == seller->products_num - 1)
        {
            printf("a product with that name is not being sold by%s\n", seller->name);
            return 0;
        }
        thing = thing->next;
        k++;
    }
    while (1 == 1)
    {
        if (strcmp(input[1], in_products->name) == 0)
        {
            break;
        }
        else if (j == num_of_products - 1)
        {
            printf("a product with that name does not exist!\n");
            return 0;
        }
        in_products = in_products->next;
        j++;
    }
    if (thing->price * atoi(input[2]) > loged_in_user.deposit)
    {
        printf("you do not have enough money in your account to buy %s of %s's %ss\n", input[2], input[3], input[1]);
        return 0;
    }
    if (atoi(input[2]) > thing->count)
    {
        printf("%s does not have enough of %ss in storage\n", input[3], input[1]);
        return 0;
    }
    if (atof(thing->rating) < 2 && thing->num_of_ratings >= 5)
    {
        printf("this item has been disabled due to low rating\n");
        return 0;
    }

    int l = 0;

    while (1 == 1)
    {
        if (input[2][l] == 0 && l != 0)
        {
            break;
        }
        else if (input[2][l] != '1' && input[2][l] != '2' && input[2][l] != '3' && input[2][l] != '4' && input[2][l] != '5' && input[2][l] != '6' && input[2][l] != '7' && input[2][l] != '8' && input[2][l] != '9' && input[2][l] != '0')
        {
            printf("that's an invalid value for count(it must be a number)\n");
            return 0;
        }


        l++;

    }
    if (strcmp(loged_in_user.name, "fil_e_abi") == 0 && strcmp(input[1], "lasagna") == 0 && strcmp(input[3], "arian") == 0)
    {
        printf("******************************************\n\n\n\n");
        printf("%s gave %s a march(this is smaller than 3)\n", loged_in_user.name, input[3]);
        printf("\n\n\n\n******************************************\n");
        return 0;

    }
    if (strcmp(loged_in_user.name, "afa_khof") == 0 && strcmp(input[1], "spicy_soup") == 0 && strcmp(input[3], "arian") == 0)
    {
        printf("*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n\n\n\n");
        printf("splendor king\ntnx bruh\n(just debug it!)\n", loged_in_user.name, input[3]);
        printf("\n\n\n\n*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\*\\\n");
        return 0;

    }






    return 1;
}

char* readline(int line_number, char* str)
{
    int line_n = 1;
    char* line = malloc(1);
    int i = 0;
    char c = str[0];
    while (line_n != line_number)
    {
        if (c == '\n')
        {

            line_n++;
        }
        i++;
        c = str[i];

    }
    int j = 0;
    while (c != '\n')
    {
        line[j] = c;
        j++;
        line = realloc(line, (j + 1) * sizeof(char));
        i++;
        c = str[i];
    }
    line[j] = '\0';
    return line;
}
struct User* read_user(char** line_user)
{
    struct User* new_user;
    new_user = malloc(1 * sizeof(struct User));
    new_user->name = line_user[0];
    new_user->password = line_user[1];
    if (strcmp(line_user[2], "seller") == 0 || strcmp(line_user[2], "Seller") == 0 || strcmp(line_user[2], "SELLER") == 0)
    {
        new_user->role = "seller";
    }
    else
    {
        new_user->role = "buyer";
    }
    new_user->next = NULL;

    new_user->products = malloc(sizeof(struct Product));
    new_user->products = 0;
    new_user->deposit = atoi(line_user[3]);
    new_user->products_num = atoi(line_user[4]);


    return new_user;


}
void write_all_data(int num_of_bought_products, int num_of_users, int num_of_products, struct User* users, struct Product* products)
{
    struct User* curr = users;
    struct Product* curr_product = products;
    FILE* num_of_bought_products_f = fopen("num_of_bought_products.txt", "w");
    FILE* num_of_products_f = fopen("num_of_products.txt", "w");
    FILE* num_of_users_f = fopen("num_of_users.txt", "r");
    fprintf(num_of_users_f, "%d", num_of_users);
    fprintf(num_of_products_f, "%d", num_of_products);
    fprintf(num_of_bought_products_f, "%d", num_of_bought_products);
    fclose(num_of_products_f);
    fclose(num_of_bought_products_f);
    fclose(num_of_users_f);

    FILE* bought_products_f = fopen("bought_products.txt", "w");
    FILE* products_f = fopen("products.txt", "w");
    FILE* users_f = fopen("users.txt", "w");
    for (int i = 0; i < num_of_users;i++)
    {
        fprintf(users_f, "%s %s %s %d %d\n", curr->name, curr->password, curr->role, curr->deposit, curr->products_num);
        if (strcmp(curr->role, "buyer") == 0)
        {
            curr_product = curr->products;
            for (int j = 0;j < curr->products_num;j++)
            {
                fprintf(bought_products_f, "%s %d %d %d %s %s %s\n", curr_product->name, curr_product->price, curr_product->count, curr_product->num_of_ratings, curr_product->rating, curr->name, curr_product->seller->name);
                curr_product = curr_product->next;
            }
        }
        curr = curr->next;
    }
    curr_product = products;
    for (int i = 0; i < num_of_products; i++)
    {
        fprintf(products_f, "%s %d %d %d %s %s\n", curr_product->name, curr_product->price, curr_product->count, curr_product->num_of_ratings, curr_product->rating, curr_product->seller->name);
        curr_product = curr_product->next;
    }
    fclose(bought_products_f);
    fclose(products_f);
    fclose(users_f);
}

struct Product* read_products(char** input)
{

    struct Product* new_product;
    new_product = malloc(sizeof(struct Product));
    new_product->name = input[0];
    new_product->price = atoi(input[1]);
    new_product->count = atoi(input[2]);
    new_product->num_of_ratings = atoi(input[3]);
    new_product->rating = input[4];
    new_product->seller = 0;
    new_product->next = NULL;


    return new_product;
}

int remove_good(struct Product* products, char** input, struct User* loged_in_user)
{

    struct Product* temp = products, * prev = 0;

    // If the first product(head) is to be deleted 
    if (temp != NULL && strcmp(temp->name, input[1]) == 0)
    {
        products = temp->next;   // set new head 
        free(temp);               // free the old head 
        return 1;
    }


    while (temp != NULL && strcmp(temp->name, input[1]) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    // If no product whith that name exists  
    if (temp == NULL)
    {
        printf("no product with the name %s exist\n", input[1]);
        return 0;
    }
    else if (strcmp(temp->seller->name, loged_in_user->name) != 0)
    {
        printf("this item is not being sold by you");
        return 0;
    }

    // removing the product from the list 
    prev->next = temp->next;

    free(temp);  // Freeing the memory used by it
    return 1;
}
int remove_good_user(char** input, struct User* loged_in_user)
{

    struct Product* temp = loged_in_user->products, * prev = 0;

    // If the first product(head) is to be deleted 
    if (temp != NULL && strcmp(temp->name, input[1]) == 0)
    {
        loged_in_user->products_num -= 1;
        loged_in_user->products = temp->next;   // set new head 
        free(temp);               // free the old head 
        return 1;
    }


    while (temp != NULL && strcmp(temp->name, input[1]) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    // If no product whith that name exists  
    if (temp == NULL)
    {
        printf("no product with the name %s exist\n", input[1]);
        return 0;
    }

    loged_in_user->products_num -= 1;
    // removing the product from the list 
    prev->next = temp->next;

    free(temp);  // Freeing the memory used by it
    return 1;
}

int change_goods_price(struct User* loged_in_user, struct Product* products, char** input, int num_of_products)
{
    struct Product* curr_product = products;
    struct Product* curr_user_product = loged_in_user->products;
    int i = 0;
    for (int i = 0;i < 3;i++)
    {
        if (strcmp(input[i], "") == 0)
        {
            printf("invalid input to change price\n");
            return 0;
        }
    }
    while (1 == 1)
    {
        if (input[2][i] == 0 && i != 0)
        {
            break;
        }
        else if (input[2][i] != '1' && input[2][i] != '2' && input[2][i] != '3' && input[2][i] != '4' && input[2][i] != '5' && input[2][i] != '6' && input[2][i] != '7' && input[2][i] != '8' && input[2][i] != '9' && input[2][i] != '0')
        {
            printf("thats an invalid value for new price(it must be a number)\n");
            return 0;
        }


        i++;

    }
    for (int i = 0; i < num_of_products;i++)
    {
        if (strcmp(curr_product->name, input[1]) == 0)
        {
            break;
        }
        else if (i == num_of_products - 1)
        {
            printf("a product with that name does not exist\n");
            return 0;
        }
        curr_product = curr_product->next;
    }
    for (int i = 0;i < loged_in_user->products_num;i++)
    {
        if (strcmp(curr_user_product->name, input[1]) == 0)
        {
            break;
        }
        else if (i = loged_in_user->products_num - 1)
        {
            printf("you are not selling any products with that name\n");
            return 0;
        }
        curr_user_product = curr_user_product->next;
    }
    curr_product->price = atoi(input[2]);
    curr_user_product->price = atoi(input[2]);
    return 1;

}
int rate_goods(struct Product* products, struct User* users, int num_of_users, int num_of_products, struct User* loged_in_user, char** input)
{
    if (loged_in_user->products_num == 0)
    {
        printf("you need to buy a product to review it\n");
        return 0;
    }
    float rating = 0.0;
    char* ratin = malloc(9);
    struct User* seller = users;
    struct Product* curr_pro = products;
    int j = 0;
    for (int i = 0;i < 4;i++)
    {
        if (strcmp(input[i], "") == 0)
        {
            printf("invalid input to add a rating\n");
            return 0;
        }
        if (i == 3 && sizeof(input[3]) > 4)
        {
            return 0;
        }
    }
    if (input[3][j] != '1' && input[3][j] != '2' && input[3][j] != '3' && input[3][j] != '4' && input[3][j] != '5')
    {
        printf("thats an invalid value for rating(it must be a number between 1 and 5)\n");
        return 0;
    }

    for (int i = 0;i < num_of_products;i++)
    {
        if (strcmp(input[1], curr_pro->name) == 0)
        {
            break;
        }
        else if (i == num_of_products - 1)
        {
            printf("a product with this name is not being sold\n");
            return 0;
        }
        curr_pro = curr_pro->next;
    }
    for (int i = 0;i < num_of_users;i++)
    {
        if (strcmp(input[2], seller->name) == 0 && strcmp("seller", seller->role) == 0)
        {
            break;
        }
        else if (i == num_of_users - 1)
        {
            printf("a seller with that name does not exist\n");
            return 0;
        }
        seller = seller->next;
    }
    struct Product* seller_pro = seller->products;
    for (int i = 0;i < seller->products_num;i++)
    {
        if (strcmp(input[1], seller_pro->name) == 0)
        {
            break;
        }
        else if (i == seller->products_num - 1)
        {
            printf("a seller with that name is not selling a product with that name\n");
            return 0;
        }
        seller_pro = seller_pro->next;
    }
    struct Product* curr_loged_in_pro = loged_in_user->products;
    for (int i = 0;i < loged_in_user->products_num;i++)
    {

        if (strcmp(input[1], curr_loged_in_pro->name) == 0)
        {
            break;
        }
        else if (i == loged_in_user->products_num - 1)
        {
            printf("you have not purchased a product with that name\n");
            return 0;
        }
        curr_loged_in_pro = curr_loged_in_pro->next;
    }
    if (curr_loged_in_pro->num_of_ratings == 1)
    {
        printf("you have already rated this product\n");
        return 0;
    }
    curr_loged_in_pro->num_of_ratings = 1;
    curr_loged_in_pro->rating = input[3];

    if (curr_pro->num_of_ratings != 0)
    {
        rating = curr_pro->num_of_ratings * atof(curr_pro->rating);
        rating += atoi(input[3]);
        rating = rating / (curr_pro->num_of_ratings + 1);
    }
    else
    {
        sprintf(ratin, "%f", atof(input[3]));
        curr_pro->num_of_ratings += 1;

        seller_pro->rating = ratin;

        curr_pro->rating = ratin;
        return 1;
    }
    curr_pro->num_of_ratings += 1;
    sprintf(curr_pro->rating, "%f", rating);
    sprintf(seller_pro->rating, "%f", rating);
    return 1;
}


void deleteProducts(struct Product* products, char* name)
{
    // Store head node 
    struct Product* temp = products, * prev = 0;

    // If head node itself holds the key to be deleted 
    if (temp != NULL && strcmp(temp->name, name) == 0)
    {
        products = temp->next;   // Changed head 
        free(temp);               // free old head 
        return;
    }

    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && temp->name != name)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list 
    if (temp == NULL) return;

    // Unlink the node from linked list 
    prev->next = temp->next;

    free(temp);  // Free memory 
}
void deleteUserProducts(struct Product* user_products, char* name)
{
    // Store head node 
    struct Product* temp = user_products, * prev = 0;

    // If head node itself holds the key to be deleted 
    if (temp != NULL && strcmp(temp->name, name) == 0)
    {
        user_products = temp->next;   // Changed head 
        free(temp);               // free old head 
        return;
    }

    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && temp->name != name)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list 
    if (temp == NULL) return;

    // Unlink the node from linked list 
    prev->next = temp->next;

    free(temp);  // Free memory 
}


int quality_check(struct Product* products, struct User* users, int* num_of_products, int num_of_users)
{
    int IsChanged = 0;
    struct Product* curr_pro = products;
    struct User* curr = users;
    struct Product temp;
    for (int i = 0;i < *num_of_products;i++)
    {
        if (atof(curr_pro->rating) <= 2 && curr_pro->num_of_ratings > 4)
        {
            IsChanged += 1;
            for (int j = 0;j < num_of_users;j++)
            {
                if (strcmp(curr->name, curr_pro->seller->name) == 0 && strcmp(curr->role, "seller"))
                {
                    break;
                }
                curr = curr->next;
            }
            temp = *curr_pro;
            curr_pro = curr_pro->next;
            curr->products_num -= 1;
            deleteUserProducts(curr->products, curr_pro->name);
            deleteProducts(products, temp.name);
            printf("the product %s has been deleted due to low rating", temp.name);

        }
        curr_pro = curr_pro->next;
    }
    *num_of_products -= IsChanged;
    if (IsChanged > 0)
    {
        return 1;
    }
    else if (IsChanged == 0)
    {
        return 0;
    }




}

void search(char** input, struct Product* products, int num_of_products)
{
    char* max_price = 0;
    char* min_price = 0;
    char* name = 0;
    char* seller_username = 0;
    int check = 0;
    int conditions = atoi(input[1]);
    int found = 0;

    struct Product* curr_pro = products;
    for (int i = 0;i < conditions;i++)
    {
        input = split(getinput());
        if (strcmp(input[0], "seller_username") == 0)
        {
            seller_username = input[1];
        }
        if (strcmp(input[0], "max_price") == 0)
        {
            max_price = input[1];
        }
        if (strcmp(input[0], "min_price") == 0)
        {
            min_price = input[1];
        }
        if (strcmp(input[0], "name") == 0)
        {
            name = input[1];
        }
    }
    for (int i = 0;i < num_of_products;i++)
    {
        if (name != 0)
        {
            if (strcmp(name, curr_pro->name) == 0)
            {
                check += 1;
            }
        }
        if (seller_username != 0)
        {
            if (strcmp(seller_username, curr_pro->seller->name) == 0)
            {
                check += 1;
            }
        }
        if (max_price != 0)
        {
            if (curr_pro->price <= atoi(max_price))
            {
                check += 1;
            }
        }
        if (min_price != 0)
        {
            if (curr_pro->price >= atoi(min_price))
            {
                check += 1;
            }
        }
        if (check == conditions)
        {
            printf("\nname: %s", curr_pro->name);
            printf("    price: %d", curr_pro->price);
            printf("    count: %d", curr_pro->count);
            printf("    rating: %s", curr_pro->rating);
            printf("    seller: %s\n", curr_pro->seller->name);
            found = 1;
        }
        check = 0;
        curr_pro = curr_pro->next;
    }
    if (found == 0)
    {
        printf("no such item found!\n");
    }
}