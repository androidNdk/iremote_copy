/**
 * Copyright (c) 2013 Egor Pushkin. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Common/Common.h"

#include "NetworkHelper.h"

#include "Config.h"

namespace RemotePC
{

	std::vector< std::string > NetworkHelper::EnumHostEndpoints()
	{
		std::vector< std::string > endpoints;

        try
        {
            boost::asio::io_service service;
            boost::asio::ip::tcp::resolver resolver(service);
            boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), Config::Instance().GetService());
            boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);
            boost::asio::ip::tcp::resolver::iterator end;

            boost::system::error_code error = boost::asio::error::host_not_found;
            while ( error && endpointIterator != end )
            {
                boost::asio::ip::tcp::endpoint endpoint = *endpointIterator++;
                if ( !endpoint.address().is_v4() )
                    continue;
                std::string address = endpoint.address().to_string();
                if ( endpoints.end() != std::find(endpoints.begin(), endpoints.end(), address) )
                    continue;
                endpoints.push_back(address);
            }
        }
        catch ( ... )
        {
            endpoints.push_back("Unknown");
        }

		return endpoints;
	}

}
