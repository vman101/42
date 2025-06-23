/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:48:41 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 16:00:04 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

#include <exception>
#include <string>

# define INTMAX_SIZE 10

typedef enum {
    T_CHAR,
    T_INT,
    T_FLOAT,
    T_DOUBLE,
    T_INFP,
    T_INFN,
    T_NAN
}   t_type;

class ScalarConverter
{
public:
    static void    convert(const std::string &);

    class EmptyInput: public std::exception {
        const char * what() const throw();
    };

    class InvalidInput: public std::exception {
        const char * what() const throw();
    };

    class NoDisplay: public std::exception {
        const char * what() const throw();
    };

    class ImpossibleConversion: public std::exception {
        const char * what() const throw();
    };

    class FloatInfPositive: public std::exception {
        const char *what() const throw();
    };

    class FloatInfNegative: public std::exception {
        const char *what() const throw();
    };

    class FloatNAN: public std::exception {
        const char *what() const throw();
    };

    class DoubleInfPositive: public std::exception {
        const char *what() const throw();
    };

    class DoubleInfNegative: public std::exception {
        const char *what() const throw();
    };

    class DoubleNAN: public std::exception {
        const char *what() const throw();
    };

private:
    ScalarConverter();
    ~ScalarConverter();

    ScalarConverter(const ScalarConverter &);
    ScalarConverter &operator=(const ScalarConverter &);

    void    detect_type(std::string& input);
    bool    is_pseudo(std::string& input);
    void    is_valid(std::string& input);

    void    conv_char(void);
    void    conv_int(void);
    void    conv_float(void);
    void    conv_double(void);

    char    get_char(void);
    int     get_int(void);
    float   get_float(void);
    double  get_double(void);

    char    c;
    int     i;
    float   f;
    double  d;

    t_type  type;

};

#endif // SCALAR_CONVERTER_HPP
