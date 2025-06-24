/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:34:57 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 19:28:27 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <exception>
#include <iostream>

int main()
{
    try {
        MutantStack<int> mstack;
        mstack.push(5);
        mstack.push(17);
        std::cout << "Stack top: " << mstack.top() << std::endl;
        mstack.pop();
        std::cout << "Stack size: " << mstack.size() << std::endl;
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        //[...]
        mstack.push(0);
        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }

        std::stack< int, std::vector<int> > s(mstack);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
