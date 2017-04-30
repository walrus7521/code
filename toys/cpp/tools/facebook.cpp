#include "facebook.h"

facebook_client& facebook_client::instance()
{
       static facebook_client c;
       return c;
}

int main()
{
}
