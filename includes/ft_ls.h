/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 00:16:37 by sharris           #+#    #+#             */
/*   Updated: 2018/11/12 00:16:37 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <stdio.h>
# include <string.h>

# include <libft.h>
# include <ft_printf.h>

/*
** Allowed functions.
**	funct name 		|	include				| desc
** _________________|_______________________|_____________
** write() 			|	unistd.h			|	you know
** opendir() 		|	dirent.h			|	Returns a "directory stream" (DIR *) NULL if error. 
** readdir()   		|	dirent.h			|	Returns a pointer to the next directory entry. NULl when reaching end of DIR or error. May not be sorted.
** closedir()		|	dirent.h			|	Closes directory strewam 0 == success; -1 == error (errno set)
** stat()			|	sys/stat			|	(char *path, struct stat) -- stat is a struct buffer that gets loaded with information. 0 success; -1 fail (errno set) 
** lstat()			|	sys/stat			|	lstat, akin to stat, but returns info about the symbolic link.
** getpwuid()		|	pwd.h sys/types.h * |	Pass uid_t, get a passwd* struct back, Null if error.
** getgrgid()		|	grp.h, *			|	Similar to the above, but with groups.
** listxattr()		|	sys/xattr.h			|	Lists extra attributes of a specified file? Needs more research
** getxattr()		|	sys/xattr.h			|	Retrieves data from extended attributes. Needs more research.
** time()			|	time.h				|	Returns time in seconds since Jan 1, 1970 coordinated uinversal time, without leap seconds.
** ctime()			|	time.h				|	Returns the strong of the current time adjusted for time zone (Needs experiementing)
** readlink()		|	unistd.h			|	Reads from a symbolic link at input path, returning number of bytes read into buf.
** malloc()			|	stdlib.h			|	you know
** free()			|	stdlib.h			|	you know
** perror()			|	stdio.h				|	Converts input value to an errno and prints it to the stderr, followed by a newline.
** strerror()		|	string.h			|	Same as abuve, but instead of printing, returns the string instead.
** exit()			|	stdlib.h			|	you know.
**
** * -- uuid/uuid.h
*/

#endif