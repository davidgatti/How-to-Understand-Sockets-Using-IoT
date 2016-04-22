// Structure for the custom data
typedef struct {
    char *in, *out;
} tuple_t;

/**
 * \brief          Replace tags with custom data
 *
 * \param input    The char array taht you want to process
 * \param output   The output char array where you want to save the new string
 * \param data     The custom structure with the data to be replaced
 */
void replace(const char* input, char* output, tuple_t *data);
