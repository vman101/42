/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:06:25 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/25 14:44:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <exception>
# include <string>
# include <map>
# include <ctime>
# include <utility>

# define DEFAULT_FILE_PATH "./data.csv"

# define FORMAT_YEAR_LEN 4
# define FORMAT_MONTH_LEN 7
# define FORMAT_DAY_LEN 10

# define BAR_FORMAT_HEADER "date | value"
# define BAR_FORMAT_SEPERATOR " | "
# define BAR_FORMAT_SEPERATOR_LEN 3

# define COMMA_FORMAT_HEADER "date,exchange_rate"
# define COMMA_FORMAT_SEPERATOR ","
# define COMMA_FORMAT_SEPERATOR_LEN 1

typedef enum {
    E_INFO,
    E_WARNING,
    E_ERROR
} E_LEVEL;

class BitcoinExchange
{
public:
    class DbFileNotOpen: public std::exception {
        const char * what() const throw();
    };

    class ParseError: public std::exception {
        public:
            ParseError(std::string message, E_LEVEL level);
            ParseError(std::string &message, E_LEVEL level);
            ParseError(const char *message, E_LEVEL level);
            virtual ~ParseError() throw();
            const char * what() const throw();
            E_LEVEL getLevel();
        private:
            std::string message;
            E_LEVEL     level;
    };

    BitcoinExchange();
    BitcoinExchange(std::string &fileopath);
    ~BitcoinExchange();

    BitcoinExchange(const BitcoinExchange &);
    BitcoinExchange &operator=(const BitcoinExchange &);

    void    extractRates(std::ifstream&) const;


private:
    std::map<unsigned int, float>   db;

    std::pair<unsigned int, float>  parseLine(std::string& line, std::string &, unsigned int, unsigned int) const;
    void                            dbInsertEntry(std::pair<unsigned int, float>);
    float                           lookupDB(unsigned int) const;
};

#endif // BITCOIN_EXCHANGE_HPP
