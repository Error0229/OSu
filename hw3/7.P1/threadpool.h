// function prototypes
void execute(void (*some_function)(void *p), void *p);
int pool_submit(void (*some_function)(void *p), void *p);
void *worker(void *param);
void pool_init(void);
void pool_shutdown(void);
