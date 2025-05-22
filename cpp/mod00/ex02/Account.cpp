/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:51:31 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/08 12:57:20 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <ctime>
#include <iostream>

int Account::_totalAmount = 0;
int Account::_nbAccounts = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

static void display_time() {
    std::time_t rawtime;
    std::time(&rawtime);
    struct tm* timeinfo = std::localtime(&rawtime);

    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", timeinfo);
    // Output the timestamp
    std::cout << "[" << buffer << "] ";
}

Account::Account( int initial_deposit ) :
    _accountIndex(_nbAccounts),
    _amount(initial_deposit),
    _nbDeposits(0),
    _nbWithdrawals(0) {
    display_time();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
    _nbAccounts++;
    _totalAmount += initial_deposit;
}

Account::Account( void ) :
    _accountIndex(_nbAccounts),
    _amount(0),
    _nbDeposits(0),
    _nbWithdrawals(0) {
}

Account::~Account() {
    display_time();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
}


int	Account::getNbAccounts( void ) {
    return _nbAccounts;
}

int	Account::getTotalAmount( void ) {
    return _totalAmount;
}

int	Account::getNbDeposits( void ) {
    return _totalNbDeposits;
}

int	Account::getNbWithdrawals( void ) {
    return _totalNbWithdrawals;
}

void	Account::makeDeposit( int deposit ) {
    display_time();
    std::cout
        << "index:" << this->_accountIndex
        << ";p_amount:" << this->_amount
        << ";deposit:" << deposit;
    this->_amount += deposit;
    this->_nbDeposits++;
    _totalAmount += deposit;
    _totalNbDeposits++;
    std::cout
        << ";amount:" << this->_amount
        << ";nb_deposits:" << this->_nbDeposits
        << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal ) {
    display_time();
    std::cout
        << "index:" << this->_accountIndex
        << ";p_amount:" << this->_amount
        << ";withdrawal:";
    if (withdrawal > this->_amount) {
        std::cout << "refused" << std::endl;
        return false;
    } else {
        this->_amount -= withdrawal;
        this->_nbWithdrawals++;
        _totalAmount -= withdrawal;
        _totalNbWithdrawals++;
        std::cout << withdrawal
            << ";amount:" << this->_amount
            << ";nb_withdrawals:" << this->_nbWithdrawals
            << std::endl;
    }

    return true;
}

int		Account::checkAmount( void ) const {
    return this->_totalAmount;
}

void	Account::displayStatus( void ) const {
    display_time();
    std::cout
        << "index:" << this->_accountIndex
        << ";amount:" << this->_amount
        << ";deposits:" << this->_nbDeposits
        << ";withdrawals:" << this->_nbWithdrawals
        <<  std::endl;
}
// [19920104_091532] index:0;amount:42;created

void    Account::displayAccountsInfos( void ) {
    display_time();
    std::cout
        << "accounts:" <<  _nbAccounts
        << ";total:" << _totalAmount
        << ";deposits:" << _totalNbDeposits
        << ";withdrawals:" << _totalNbWithdrawals
        << std::endl;
}
