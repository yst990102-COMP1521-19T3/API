#define secret_hash_define 1

// secret comment

int secret_global_variable;

int secret_function_name(char *s) {
    return 0;
}

int main(void) {
    int secret_local_variable = 0;
    char *s = "secret string";
    secret_function_name(s);
    return secret_local_variable;
}
