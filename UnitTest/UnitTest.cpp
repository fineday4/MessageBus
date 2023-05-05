#include <gtest/gtest.h>
#include <iostream>
#include "MessageBus.h"

using namespace std;

TEST(MessageBus, case1) {
    MessageBus* bus = AbstraceFactory::getObject<MessageBus*>("MessageBus");
    
    cout << "Attach Before" << endl;
    bus->Attach([](int a) { cout << "no reference a: " << a << endl;});
    bus->Attach([](int &a) { cout << "lvalue reference a: " << a << endl;});
    bus->Attach([](int &&a) { cout << "rvalue reference a: " << a << endl;});
    bus->Attach([](const int &a) { cout << "const lvalue reference a: " << a << endl;});
    bus->Attach([](int a) {cout << "no reference has return value and key " << a << endl; return a;}, "a");
    cout << "Attach After" << endl;

    int i = 2;
    cout << "SendReq Before" << endl;
    bus->SendReq<void, int>(2);
    bus->SendReq<int, int>(2, "a");
    bus->SendReq<void, int&>(i);
    bus->SendReq<void, const int&>(2);
    bus->SendReq<void, int&&>(2);
    cout << "SendReq After" << endl;
    
    cout << "Remove Before" << endl;
    bus->Remove<void, int>();
    bus->Remove<int, int>("a");
    bus->Remove<void, int&>();
    bus->Remove<void, const int&>();
    bus->Remove<void, int&&>();
    cout << "Remove After" << endl;

    cout << "SendReq Before" << endl;
    bus->SendReq<void, int>(2);
    bus->SendReq<int, int>(2, "a");
    bus->SendReq<void, int&>(i);
    bus->SendReq<void, const int&>(2);
    bus->SendReq<void, int&&>(2);
    cout << "SendReq After" << endl;

}

