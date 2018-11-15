#include <libft.h>
#include <ft_ls.h>

/*
** Adapting t_list function to help with radix sort.
** content_size -> Holds string length
** data -> holds the string
** next-> Points to the next in the list.
*/

// ! NOTE!!!
// ! --- I'm probably going to scrap this, this is looking to be a malloc hell and dealing with the potential leaks looks to be hell. :c
// ! and considering variable length strings is kind of a problem, and writing the code to manage and insert into two different linked lists. 
// ! Since I can't choose the size of my arrow in middle of the function (according to the Norme) Linked lists are my onlw option, and it's oging to be a disaster to manage.
// ! Hearing that quicksort can sort in-place sounds like it's going to be the optimal choice, and it seems to have similar or better efficiency to the radix.
// ! Not to mention, some foresight into this looks like it's goign to be difficult writing it around the Norme as well.
// ! Tomorrow, lets look into quick sort algorithm. :3

// ! Sorry for the lack of comments. The basic idea is to use linked lists to store the buckets, and a linked list in each bucket to put each notable character in question.
// ! A part of me wants to tackle this for the challenge, but another part says it isnt' worth it and my time would better be spent on other things. xD

t_list *string_to_list(char **strings)
{
	t_list *start;
	t_list *new;
	int i;

	i = -1;
	start = NULL;
	while (strings[++i])
		ft_lstadd(&start, ft_lstnew(strings[i], ft_strlen(strings[i]) + 1));
	return(start);
}

int get_chardiff_tally(t_list *lsts, int ind)
{
	int tally[128];
	char *s;
	int n;
	int i;

	ft_bzero(tally, sizeof(int) * 128);
	while (lsts)
	{
		if (ind > lsts->content_size)
			tally[0]++;
		else
		{
			s = lsts->content;
			tally[s[ind]]++;
		}
		lsts = lsts->next;
	}
	i = 0;
	n = 0;
	while (i < 128)
		n += tally[i++] && 1;
	if (n > 1)
		return (n);
	else
		return(tally[0] > 0 ? -1 : 1);
}

int get_buckets(t_list *lsts, int ind)
{
	int tally[128];
	t_list *blst;
	char *s;
	int n;
	int i;

	buckets = NULL;
	ft_bzero(tally, sizeof(int) * 128);
	while (lsts)
	{
		if (ind > lsts->content_size)
			add_to_bucket(blst, 0);
		else
		{
			s = lsts->content;
			tally[s[ind]]++;
		}
		lsts = lsts->next;
	}
	i = 0;
	n = 0;
	while (i < 128)
		n += tally[i++] && 1;
	if (n > 1)
		return (n);
	else
		return(tally[0] > 0 ? NULL : buckets);
}

t_bucket *new_bucket(char c)
{
	t_bucket *bucket;

	bucket = ft_memalloc(sizeof(bucket));
	bucket->c = c;
	bucket->lst = NULL;
	return (bucket);
}

void add_to_buckets(t_list **alst, t_list lst, char c)
{
	t_list *tmp;
	t_bucket *btmp;

	if (alst == NULL || *alst == NULL)
		ft_lstadd(alst, ft_lstnew(new_bucket(c), sizeof(t_bucket)));
	else
	{
		tmp = *alst;
		while (tmp)
		{
			btmp = tmp->content;
			if (btmp->c == c)
				return ;
			tmp = tmp->next;
		}
		ft_lstadd(alst, ft_lstnew(new_bucket(c), sizeof(t_bucket)));
	}
}

t_list *radix_sort(t_list *lst)
{
	
}

int main(int ac, char **av)
{
	t_list *strings = string_to_list(av);
	t_list *tmp = strings;

	av[ac] = 0;
	while(tmp)
	{
		printf("%s", (char *)tmp->content);
		printf("-- A list\n");
		tmp = tmp->next;
	}
	printf("Diffs: %d\n", get_chardiff_tally(strings, 20));
	return(0);
}

// int get_pos_tally()

// t_list *ft_radixsort(char **strings)
// 	int tally[128];

// }