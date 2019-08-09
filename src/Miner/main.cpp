// Copyright (c) 2019, Zpalmtree
//
// Please see the included LICENSE file for more information.

#include <iostream>

#include "PoolCommunication/PoolCommunication.h"
#include "Types/Pool.h"
#include "Utilities/ColouredMsg.h"
#include "Utilities/Input.h"
#include "Utilities/String.h"

Pool getPool()
{
    Pool pool;

    while (true)
    {
        std::cout << InformationMsg("Enter the pool address to mine to.") << std::endl
                  << InformationMsg("This should look something like trtl.pool.mine2gether.com:3335: ");

        std::string address;
        std::string host;
        uint16_t port;

        if (!std::getline(std::cin, address))
        {
            return pool;
        }

        Utilities::trim(address);

        if (!Utilities::parseAddressFromString(host, port, address))
        {
            std::cout << WarningMsg("Invalid pool address! Should be in the form host:port, for example, trtl.pool.mine2gether.com:3335!")
                      << std::endl;

            continue;
        }

        pool.host = host;
        pool.port = port;

        break;
    }

    std::cout << InformationMsg("\nEnter your pool login. This is usually your wallet address: ");

    std::string login;

    if (!std::getline(std::cin, login))
    {
        return pool;
    }

    pool.username = login;

    std::cout << InformationMsg("\nEnter the pool password. You can usually leave this blank, or use 'x': ");

    std::string password;

    if (!std::getline(std::cin, password))
    {
        return pool;
    }

    pool.password = password;

    std::cout << InformationMsg("\nEnter the rig ID to use with this pool. This can identify your different computers to the pool.") << std::endl
              << InformationMsg("You can leave this blank if desired: ");

    std::string rigID;

    if (!std::getline(std::cin, rigID))
    {
        return pool;
    }

    pool.rigID = rigID;

    return pool;
}

std::vector<Pool> getPools()
{
    std::vector<Pool> pools;

    while (true)
    {
        const Pool pool = getPool();

        pools.push_back(pool);

        if (!Utilities::confirm("\nWould you like to add another pool?", false))
        {
            break;
        }

        std::cout << std::endl;
    }

    return pools;
}

int main()
{
    std::vector<Pool> pools = getPools();

    PoolCommunication pool(pools);

    pool.login();
}
