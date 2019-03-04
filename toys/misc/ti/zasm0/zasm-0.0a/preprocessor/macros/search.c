/***********************************************************************************\
 * Copyright (C) 2004 Steven Deprez                                                *
 *                                                                                 *
 * This file is part of zasm                                                       *
 *                                                                                 *
 * zasm is free software; you can redistribute it and/or modify                    *
 * it under the terms of the GNU General Public License as published by            *
 * the Free Software Foundation; either version 2 of the License, or               *
 * (at your option) any later version.                                             *
 *                                                                                 *
 * This program is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   *
 * GNU General Public License for more details.                                    *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License               *
 * along with this program; if not, write to the Free Software                     *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.     *
 *                                                                                 *
 * In addition, as a special exception, Peter-Martijn Kuipers gives permission     *
 * to link the code of this program with the appsign library, and distribute       *
 * linked combinations including the two. If you modify this file, you may extend  *
 * this exception to your version of the file, but you are not obligated to do so. *
 * If you do not wish to do so, delete this exception statement form your version. *
\***********************************************************************************/

#define large ((struct macro_search_large_t *)tree)
#define small ((struct macro_search_small_t *)tree)

static int macro_search_replace(struct macro_search_t *tree,
				struct macro_search_t *orig,
				struct macro_search_t *new)
{
  int c;
  if (!tree)
    ERROR("internal error\n");
  switch (tree->type)
    {
    case MACRO_SEARCH_LARGE:
      for (c = 0; c < 63; c++)
	if (large->children[c] == orig)
	  {
	    large->children[c] = new;
	    return 0;
	  }
      return -1;
    case MACRO_SEARCH_SMALL:
      for (c = 0; c < small->child_count; c++)
	if (small->children[c] == orig)
	  {
	    small->children[c] = new;
	    return 0;
	  }
      return -1;
    default:
      ERROR("internal error\n");
    }

}

static struct macro_search_t *macro_search_make_small(struct macro_t *macro, 
						      struct macro_search_t **children, 
						      char *mapping, 
						      int child_count)
{
  struct macro_search_small_t *new_s = NULL;
  int i;

  ALLOCATE(struct macro_search_small_t, new_s, 1);
  new_s->head.type = MACRO_SEARCH_SMALL;
  new_s->head.parent = NULL;
  new_s->head.macro = macro;
  if (child_count)
    {
      ALLOCATE(char, new_s->mapping, child_count+1);
      ALLOCATE(struct macro_search_t *, new_s->children, child_count);
      for (i = 0; i < child_count; i++)
	{
	  new_s->mapping[i] = mapping[i];
	  new_s->children[i] = children[i];
	}
      new_s->mapping[child_count] = 0;
    }
  else
    {
      new_s->mapping = NULL;
      new_s->children = NULL;
    }
  new_s->child_count = child_count;
  return (struct macro_search_t *)new_s;
}

static struct macro_search_t *macro_search_make_small_tree(struct macro_t *macro, char *name)
{
  struct macro_search_t *next = NULL;
  struct macro_search_t *new_s = NULL;
  if (name[0])
    {
      if (!(next = macro_search_make_small_tree(macro, name+1)))
	ERROR("internal error\n");
      if (!(new_s = macro_search_make_small(NULL, &next, name, 1)))
	ERROR("internal error\n");
      next->parent = new_s;
      return new_s;
    }
  return macro_search_make_small(macro, NULL, NULL, 0);
}

static struct macro_search_t *macro_search_get_next(struct macro_search_t *tree, char *name)
{
  int c;
  if (!tree)
    return NULL;
  switch (tree->type)
    {
    case MACRO_SEARCH_LARGE:
      if ((c = MACRO_GET_CHAR(name[0]))<0)
	ERROR("internal error\n");
      return large->children[c];
    case MACRO_SEARCH_SMALL:
      if ((c = instr_index(name[0], small->mapping))<0)
	return NULL;
      return small->children[c];
    default:
      ERROR("internal error\n");
    }
}

static struct macro_search_t *macro_search_find(struct macro_search_t *tree, char *name)
{
  if (!name)
    return NULL;
  for (; *name; name++)
    if (!(tree = macro_search_get_next(tree, name)))
      return NULL;
  if (!tree->macro)
    return NULL; // don't return a tree without macro
  return tree;
}

static int macro_search_child_count(struct macro_search_t *tree)
{
  int i, c = 0;

  if (!tree)
    return 0;
  switch (tree->type)
    {
    case MACRO_SEARCH_LARGE:
      for (i = 0; i < 63; i++)
	if (large->children[i])
	  c++;
      break;
    case MACRO_SEARCH_SMALL:
      c = small->child_count;
      break;
    default:
      ERROR("internal error\n");
    }
  if (tree->macro)
    c++;
  return c;
}


static void macro_search_free(struct macro_search_t *tree)
{
  int c;
  if (!tree)
    return;
  if (tree->macro)
    macro_free(tree->macro);
  switch (tree->type)
    {
    case MACRO_SEARCH_LARGE:
      for (c = 0; c < 63; c++)
	macro_search_free(large->children[c]);
      break;
    case MACRO_SEARCH_SMALL:
      for (c = 0; c < small->child_count; c++)
	macro_search_free(small->children[c]);
      free(small->children);
      free(small->mapping);
      break;
    default:
      ERROR("internal error\n");
    }
  free(tree);
}


// no realloc nor degrade: save some time
static void macro_search_unlink(struct macro_search_t *tree, struct macro_search_t *node)
{
  int i, c;

  switch (tree->type)
    {
    case MACRO_SEARCH_LARGE:
      for (c = 0; c < 63; c++)
	if (large->children[c] == node)
	  large->children[c] = NULL;
      return;
    case MACRO_SEARCH_SMALL:
      for (c = 0; c < small->child_count; c++)
	{
	  if (small->children[c] == node)
	    break;
	}
      if (c >= small->child_count)
	return;
      small->child_count--;
      for (i = c; i < small->child_count; i++)
	{
	  small->mapping[i] = small->mapping[i+1];
	  small->children[i] = small->children[i+1];
	}
      small->mapping[i] = 0;
      return;
    default:
      ERROR("internal error\n");
    }
}

static void macro_search_del_intern(struct macro_search_t *tree)
{
  if (!tree)
    return; // none removed
  if (macro_search_child_count(tree->parent) == 1)
    {
      macro_search_del_intern(tree->parent);
      return;
    }
  if (tree->parent)
    macro_search_unlink(tree->parent,tree);
  else
    macro_tree = NULL;
  macro_search_free(tree);
  return;
}

static int macro_add_intern(struct macro_t *macro, struct macro_search_t *tree, char *name)
{
  struct macro_search_t *next;
  struct macro_search_large_t *new_l;
  int c;

  if (!tree)
    {
      if (macro_tree)
	ERROR("internal error\n");
      if (!(next = macro_search_make_small_tree(macro, name)))
	ERROR("internal error\n");
      next->parent = NULL;
      macro_tree = next;
      return 0;
    }
      
  if ((next = macro_search_get_next(tree, name)))
    return macro_add_intern(macro, next, name+1);

  // is this the right node?
  if (!name[0])
    {
      if (tree->macro)
	return -2; // name already in use
      tree->macro = macro;
      return 0;
    }
	
  switch (tree->type)
    {
    case MACRO_SEARCH_LARGE:
      if ((c = MACRO_GET_CHAR(name[0])) < 0)
	ERROR("invalid macro name\n");
      if (large->children[c])
	return -2; // the needed node exists ??
      if (!(next = macro_search_make_small_tree(macro, name+1)))
	ERROR("internal error\n");
      next->parent = tree;
      large->children[c] = next;
      return 0;
    case MACRO_SEARCH_SMALL:
      if (instr(name[0], small->mapping))
	return -2; // needed node exists ??
      if (MACRO_GET_CHAR(name[0]) < 0)
	ERROR("invalid macro name\n");
      if (small->child_count == 47)
	{ // become MACRO_SEARCH_LARGE
	  ALLOCATE(struct macro_search_large_t, new_l, 1);
	  new_l->head.type = MACRO_SEARCH_LARGE;
	  new_l->head.parent = tree->parent;
	  new_l->head.macro = tree->macro;
	  for (c = 0; c < 63; c++)
	    new_l->children[c] = NULL;
	  for (c = 0; c < small->child_count; c++)
	    {
	      small->children[c]->parent = (struct macro_search_t *)new_l;
	      new_l->children[MACRO_GET_CHAR(small->mapping[c])] = small->children[c];
	    }
	  if ((c = MACRO_GET_CHAR(name[0])) < 0)
	    ERROR("invalid macro name\n");
	  if (!(next = macro_search_make_small_tree(macro, name+1)))
	    ERROR("internal error\n");
	  next->parent = (struct macro_search_t *)new_l;
	  new_l->children[c] = next;
	  if (tree->parent)
	    {
	      if (macro_search_replace(tree->parent, tree, (struct macro_search_t *)new_l)<0)
		ERROR("internal error\n");
	    }
	  else
	    {
	      // root node
	      macro_tree = (struct macro_search_t *)new_l;
	    }
	  free(small->children);
	  free(small->mapping);
	  free(tree);
	  return 0;
	}
      small->child_count++;
      REALLOCATE(char, small->mapping, small->child_count+1);
      REALLOCATE(struct macro_search_t *, small->children, small->child_count);
      small->mapping[small->child_count-1] = name[0];
      small->mapping[small->child_count] = 0;
      if (!(next = macro_search_make_small_tree(macro, name+1)))
	ERROR("internal error\n");
      next->parent = tree;
      small->children[small->child_count-1] = next;
      return 0;
    default:
      ERROR("internal error\n"); // nonexistant type
    }
}

// for debugging purposes only !!
// prints out a visual representation of the tree
static int macro_print_intern(struct macro_search_t *tree, int depth)
{
  int i, j;

  if (!tree)
    {
      if (depth)
	ERROR("internal error\n")
      else
	return 0;
    }

  for (j = 0; j < depth; j++)
    DEBUG("  ");
  if (tree->type == MACRO_SEARCH_LARGE)
    DEBUG("LARGE(child_count=%i)", macro_search_child_count(tree))
  else if (tree->type == MACRO_SEARCH_SMALL)
    DEBUG("SMALL(\"%s\")", small->mapping)
  else
    DEBUG("(invalid)")
  if (tree->macro)
    DEBUG(": \"%s\"\n", tree->macro->name)
  else
    DEBUG("\n")
  switch (tree->type)
    {
    case MACRO_SEARCH_LARGE:
      for (i = 0; i < 63; i++)
	if (large->children[i])
	  macro_print_intern(large->children[i], depth+1);
      return 0;
    case MACRO_SEARCH_SMALL:
      for (i = 0; i < small->child_count; i++)
	if (small->children[i])
	  macro_print_intern(small->children[i], depth+1);
      return 0;
    default:
      ERROR("internal error\n");
    }
}

#undef large
#undef small
