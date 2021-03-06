
#ifndef UMAKE_H
#define UMAKE_H

extern struct rule
{
	struct rule *next;
	struct rule *chain;
	int done;
	
	char *output;
	char **input;
	char **cmds;
} *rules;

extern struct var
{
	struct var *next;
	char *name;
	char *val;
} *vars;

extern const char **incpaths;
extern int incpathcnt;
extern int vflag;

static struct rule *find_rule(const char *output);
int load(const char *pathname);
int make(struct rule *r, const char *src, const char *target);
void setvar(const char *name, const char *value);
char *substvars(const char *s);

#endif
