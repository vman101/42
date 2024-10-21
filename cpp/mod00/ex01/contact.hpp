/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:06:56 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/21 16:19:19 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class Contact
{
	public:
		Contact();
		~Contact();

		std::string	FirstNameGet() const;
		std::string	LastNameGet() const;
		std::string	NickNameGet() const;
		Contact		DefineNew( void );
		int			PhoneNumberGet() const;

		void	FirstNameSet(std::string first_name);
		void	LastNameSet(std::string last_name);
		void	NickNameSet(std::string nick_name);
		void	PhoneNumberSet();

		void	Display( void );
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nick_name;
		std::string	phone_number;
		std::string	darkest_secret;
};
