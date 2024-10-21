/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:40:37 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/21 11:30:26 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"

#define MAX_CONTACT 8

class Phonebook
{
	public:
		Phonebook( void );
		~Phonebook( void );

		void	Add( void );
		void	Search( void );
		void	Display( void );
	private:
		int		contact_cursor;
		int		contact_count;
		Contact	contact[8];
};
