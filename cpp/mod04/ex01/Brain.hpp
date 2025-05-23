/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:30:57 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 17:09:35 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_CPP
# define BRAIN_CPP

# include <string>

# define MAX_IDEAS 100

class Brain
{
public:
    Brain();
    ~Brain();

    Brain(const Brain &);
    Brain &operator=(const Brain &);

    void            haveIdea(const std::string&);
    std::string     expressIdea(int index);

private:
    std::string _ideas[MAX_IDEAS];
    int         _idea_index;
};

#endif // BRAIN_CPP
