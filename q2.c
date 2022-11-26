#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS (25)

typedef struct {
    int year;
    int month;
    int day;
} date_t;

typedef struct {
    char *name;
    char *category;
    char *barcode;
    int amount;
    double price;
    date_t *expire_date;
} product_t;

typedef struct {
    product_t *products[MAX_PRODUCTS];
    int number_of_products;
} store_t;


product_t *create_product(const char *name, const char *category, const char
*barcode, int amount, double price, date_t *expire_date)
{
    product_t *product=malloc(sizeof(product_t));
    product->name=malloc((strlen(name)+1));
    product->category=malloc((strlen(category)+1));
    product->barcode=malloc((strlen(barcode)+1));
    product->expire_date=malloc(sizeof(date_t));
    if (NULL==product->name || NULL==product->category || NULL==product->barcode || NULL==product->expire_date || NULL==product)
    {
        free (product->name);
        free (product->category);
        free (product->barcode);
        free(product->expire_date);
        free(product);
        return NULL;
    }
    strcpy(product->name,name);
    strcpy(product->category,category);
    strcpy(product->barcode,barcode);
    if (0==strlen(product->name) || 0==strlen(product->category) || 0==strlen(product->barcode) || amount<=0 || (NULL==product->expire_date))
    {
        free (product->name);
        free (product->category);
        free (product->barcode);
        free(product->expire_date);
        free(product);
        return NULL;
    }
    else
    {
        product->amount = amount;
        product->price = price;
        product->expire_date=expire_date;
    }
    return product;
}

void print_product(const product_t *product)
{
    printf("Product %s [%s]\n", product->name, product->barcode);
    printf("Category: %s\n", product->category);
    printf("Price: %lf\n", product->price);
    printf("Amount: %d\n", product->amount);
    printf("Expires: %d/%d/%d\n\n", product->expire_date->day, product->expire_date->month, product->expire_date->year);
}

/*answer of the theoretical question:
*in order to change the place of MAX_PRODUCTS and make it dynamically instead of statically , we should use the
*operation malloc() and we need to pass an extra parameter that it presents the number of products. so after this,
*in help with the function malloc() and realloc() we free the unnecessary bytes located in memory and after we finish from doing operations
*with the need of number of products we can free the bytes located for this operator and that is more dynamically*/


int add_product(store_t *store, product_t *product)
{
    if (NULL==store|| NULL==product)
    {
        return -1;
    }
    for (int i=0;i < store->number_of_products;i++)
    {
        if (0==strcmp(product->barcode,store->products[i]->barcode))
        {
            store->products[i]->amount=store->products[i]->amount+ product->amount;
            free(product);
            return 0;
        }
    }
    store->products[store->number_of_products] = product;
    ++store->number_of_products;
    return 0;
}
int remove_product(store_t *store, const char *barcode)
{
    for (int i=0;i<store->number_of_products;i++)
    {
        if (0==strcmp(barcode,store->products[i]->barcode))
        {
            product_t *temp = store->products[i];
            store->products[i] = store->products[store->number_of_products-1];
            free(temp);
            store->number_of_products--;
            return 0;
        }
    }
    return -1;
}
void print_products(store_t *store)
{
    if (NULL==store)
    {
        return;
    }
    else
    {
        for(int j=0;j<store->number_of_products;j++)
        {
            print_product(store->products[j]);
        }
    }
    
}
void print_expired_products(store_t *store, date_t *now)
{
    if (NULL==store || NULL==now)
    {
        return;
    }
    else
        for(int j=0;j<store->number_of_products;j++)
        {
            if (store->products[j]->expire_date->year < now->year)
            {
                print_product(store->products[j]);
            }
            else if (store->products[j]->expire_date->month < now->month)
            {
                print_product(store->products[j]);
            }
            else if (store->products[j]->expire_date->day < now->day)
            {
                print_product(store->products[j]);
            }
        }
}
void print_category(store_t *store, const char *category)
{
    if (NULL==store)
    {
        return;
    }
    if (NULL==category)
    {
        print_products(store);
    }
    else
    {
        for(int i=0;i<store->number_of_products;i++)
        {
            if (0==strcmp(store->products[i]->category,category))
            {
                print_product(store->products[i]);
            }
        }
    }
    
}

