//
//  main.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include "Scanner.h"
#include "Parser.h"
#include "Node.h"
#include "Calc.h"
#include "Exception.h"
#include <iostream>
using namespace std;

int main(void)
{
    Calc calc;
    STATUS status = STATUS_OK;
    do
    {
        cout << "> ";
        string buf;
        getline(cin, buf);
        Scanner scanner(buf);
        Parser parse(scanner, calc);
        try
        {
            parse.Parse();
        }
        catch (SynatxError& se)
        {
            cout << se.what() << endl;
        }
        catch (Exception& e)
        {
            cout << e.what() << endl;
        }
        catch (...)
        {
            cout << "internal error." << endl;
        }
        
        cout << parse.Calculate() << endl;
    }
    while(status != STATUS_QUIT);
    return 0;
}
