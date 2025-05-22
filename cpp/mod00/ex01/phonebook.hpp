/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:40:37 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/07 17:00:40 by vvobis           ###   ########.fr       */
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
		Contact	contact[MAX_CONTACT];
};
