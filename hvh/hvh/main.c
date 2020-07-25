#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"



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
int main()
{
    FILE* users_f = fopen("users.txt", "r+");
    FILE* num_of_users_f = fopen("num_of_users.txt", "r");
    FILE* products_f = fopen("products.txt", "r+");
    FILE* num_of_products_f = fopen("num_of_products.txt", "r");
    FILE* num_of_bought_products_f = fopen("num_of_bought_products.txt", "r");
    FILE* bought_products_f = fopen("bought_products.txt", "r+");
    char* bought_products_str = readFile(bought_products_f);
    char* products_str = readFile(products_f);
    char* users_str = readFile(users_f);

    fclose(products_f);
    fclose(users_f);
    struct User* users;
    struct User* temp_user;
    struct User* loged_in_user = 0;
    struct User* curr;
    struct Product* products = NULL;
    struct Product* curr_product = 0;
    struct Product* temp_product;
    users = malloc(1 * sizeof(struct User));
    products = malloc(1 * sizeof(struct Product));

    char** input;
    char** line_user;
    char** line_products;
    int num_of_users = atoi(readFile(num_of_users_f));
    fclose(num_of_users_f);
    int num_of_products = atoi(readFile(num_of_products_f));
    fclose(num_of_products_f);
    int num_of_bought_products = atoi(readFile(num_of_bought_products_f));
    fclose(num_of_bought_products_f);
    int user_num;
    int command = 0;
    int loged_in = 0;
    //loading saved data to memory
    //1. loading users and their products
    products = NULL;
    for (int i = 0;i < num_of_users;i++)
    {
        line_user = split(readline(i + 1, users_str));
        temp_user = read_user(line_user);
        for (int j = 0;j < num_of_products;j++)
        {
            line_products = split(readline(j + 1, products_str));

            if (strcmp(temp_user->name, line_products[5]) == 0 && strcmp(temp_user->role, "seller") == 0)
            {
                temp_product = read_products(line_products);
                temp_product->seller = temp_user;
                temp_product->next = temp_user->products;
                temp_user->products = temp_product;
            }
        }

        temp_user->next = users;
        users = temp_user;
    }
    //2. loading the products
    for (int i = 0;i < num_of_products;i++)
    {
        line_products = split(readline(i + 1, products_str));
        temp_product = read_products(line_products);
        curr = users;
        for (int j = 0; j < num_of_users; j++)
        {
            if (strcmp(curr->name, line_products[5]) == 0)
            {
                temp_product->seller = curr;
                break;
            }
            curr = curr->next;
        }
        temp_product->next = products;
        products = temp_product;

    }



    //3. loading the bought products
    struct User* seller = users;
    for (int i = 0;i < num_of_bought_products;i++)
    {
        curr = users;
        seller = users;
        line_products = split(readline(i + 1, bought_products_str));
        temp_product = read_products(line_products);
        for (int j = 0; j < num_of_users; j++)
        {
            if (strcmp(seller->name, line_products[6]) == 0 && strcmp(seller->role, "seller") == 0)
            {
                temp_product->seller = seller;
                break;
            }
            seller = seller->next;
        }
        for (int j = 0; j < num_of_users; j++)
        {
            if (strcmp(curr->name, line_products[5]) == 0 && strcmp(curr->role, "buyer") == 0)
            {
                temp_product->next = curr->products;
                curr->products = temp_product;
                break;
            }
            curr = curr->next;
        }

    }

    printf("        ******////// welcome to ut-kala \\\\\\\\\\\\******\n");
    while (1 == 1)
    {

        while (loged_in == 0)
        {
            input = split(getinput());
            command = command_check(input);
            if (command == 1)
            {
                if (check_signup(input, users, num_of_users) == 1)
                {
                    num_of_users += 1;
                    num_of_users_f = fopen("num_of_users.txt", "w");
                    fprintf(num_of_users_f, "%d", num_of_users);
                    fclose(num_of_users_f);
                    temp_user = signup(input);
                    FILE* new_user = fopen("users.txt", "a");
                    fprintf(new_user, "%s %s %s %d %d\n", temp_user->name, temp_user->password, temp_user->role, temp_user->deposit, temp_user->products_num);
                    fclose(new_user);

                    temp_user->next = users;
                    users = temp_user;

                    command = 0;
                }
            }
            if (command == 2)
            {
                loged_in = login(input, users, num_of_users, &user_num);
                if (loged_in == 1 || loged_in == 2)
                {
                    loged_in_user = users;
                    for (int i = 0;i < user_num;i++)
                    {
                        loged_in_user = loged_in_user->next;
                    }

                }
                command = 0;
            }
            if (command == 3)
            {
                mergeSort(&products);
                show_goods(products, num_of_products);
                command = 0;
            }


        }
        while (loged_in == 1)
        {//loged in as seller
            input = split(getinput());
            command = seller_command_check(input);
            if (command == 1)
            {
                logout(&loged_in);
                command = 0;
            }
            if (command == 2)
            {
                view_user(*loged_in_user);
                command = 0;
            }
            if (command == 3)
            {

                if (check_add_goods(input, products, num_of_products, loged_in_user) == 1)
                {
                    num_of_products += 1;

                    temp_product = add_goods(input, loged_in_user);
                    products_f = fopen("products.txt", "a");
                    fprintf(products_f, "%s %d %d %d %s %s\n", temp_product->name, temp_product->price, temp_product->count, temp_product->num_of_ratings, temp_product->rating, temp_product->seller->name);
                    fclose(products_f);
                    temp_product->next = products;
                    products = temp_product;
                    num_of_products_f = fopen("num_of_products.txt", "w");
                    fprintf(num_of_products_f, "%d", num_of_products);
                    fclose(num_of_products_f);


                    users_f = fopen("users.txt", "w");
                    curr = users;
                    for (int i = 0; i < num_of_users;i++)
                    {
                        fprintf(users_f, "%s %s %s %d %d\n", curr->name, curr->password, curr->role, curr->deposit, curr->products_num);
                        curr = curr->next;
                    }
                    fclose(users_f);
                    command = 0;

                }
                write_all_data(num_of_bought_products, num_of_users, num_of_products, users, products);
            }
            if (command == 4)
            {
                mergeSort(&products);

                show_goods(products, num_of_products);
                command = 0;
            }
            if (command == 5)
            {
                if (remove_good(products, input, loged_in_user) == 1)
                {
                    remove_good_user(input, loged_in_user);
                    num_of_products -= 1;
                    write_all_data(num_of_bought_products, num_of_users, num_of_products, users, products);
                    printf("the product has been successfully removed\n");

                }
            }
            if (command == 6)
            {
                if (change_goods_price(loged_in_user, products, input, num_of_products) == 1)
                {
                    write_all_data(num_of_bought_products, num_of_users, num_of_products, users, products);
                    printf("price successfuly changed\n");
                }
            }
            if (command == 7)
            {
                mergeSort(&products);
                search(input, products, num_of_products);

            }

        }
        while (loged_in == 2)
        {//loged in as buyer
            input = split(getinput());
            command = buyer_command_check(input);
            if (command == 1)
            {
                logout(&loged_in);
                command = 0;
            }
            if (command == 2)
            {
                view_user(*loged_in_user);
                command = 0;
            }
            if (command == 3)
            {
                deposit(loged_in_user, input);
                users_f = fopen("users.txt", "w");
                curr = users;
                for (int i = 0; i < num_of_users;i++)
                {
                    fprintf(users_f, "%s %s %s %d %d\n", curr->name, curr->password, curr->role, curr->deposit, curr->products_num);
                    curr = curr->next;
                }
                fclose(users_f);
            }
            if (command == 4)
            {
                mergeSort(&products);

                show_goods(products, num_of_products);
                command = 0;
            }
            if (command == 5)
            {
                if (check_buy(input, products, num_of_products, users, num_of_users, *loged_in_user))
                {
                    buy(input, products, num_of_products, loged_in_user, users, num_of_users);
                    num_of_bought_products += 1;
                    write_all_data(num_of_bought_products, num_of_users, num_of_products, users, products);
                    printf("item successfully purchased!\n");
                    command = 0;
                }
            }
            if (command == 6)
            {
                if (rate_goods(products, users, num_of_users, num_of_products, loged_in_user, input) == 1)
                {
                    write_all_data(num_of_bought_products, num_of_users, num_of_products, users, products);
                    printf("rating successfuly recorded\n");
                }
            }
            if (command == 7)
            {
                mergeSort(&products);
                search(input, products, num_of_products);

            }
        }
    }
    return 0;
}
