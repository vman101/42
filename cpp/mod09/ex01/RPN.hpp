/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:22:06 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/25 16:08:50 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <sstream>
# include <stack>

typedef enum {
    OP_PLUS = '+',
    OP_MINUS = '-',
    OP_MUL = '*',
    OP_DIV = '/'
} op;

typedef enum {
    E_INFO,
    E_WARNING,
    E_ERROR
} E_LEVEL;

class RPN
{
public:
    RPN();
    RPN(std::stringstream &);
    ~RPN();

    RPN(const RPN &);
    RPN &operator=(const RPN &);

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


private:
    void            doOp(op);
    std::stack<int> stack;
};

#endif // RNP_HPP
