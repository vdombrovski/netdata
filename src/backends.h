// SPDX-License-Identifier: GPL-3.0+
#ifndef NETDATA_BACKENDS_H
#define NETDATA_BACKENDS_H 1

typedef enum backend_options {
    BACKEND_OPTION_NONE              = 0,

    BACKEND_SOURCE_DATA_AS_COLLECTED = (1 << 0),
    BACKEND_SOURCE_DATA_AVERAGE      = (1 << 1),
    BACKEND_SOURCE_DATA_SUM          = (1 << 2),

    BACKEND_OPTION_SEND_NAMES        = (1 << 16)
} BACKEND_OPTIONS;

#define BACKEND_OPTIONS_SOURCE_BITS (BACKEND_SOURCE_DATA_AS_COLLECTED|BACKEND_SOURCE_DATA_AVERAGE|BACKEND_SOURCE_DATA_SUM)
#define BACKEND_OPTIONS_DATA_SOURCE(backend_options) (backend_options & BACKEND_OPTIONS_SOURCE_BITS)

extern int global_backend_update_every;
extern BACKEND_OPTIONS global_backend_options;
extern const char *global_backend_prefix;

extern void *backends_main(void *ptr);

extern int backends_can_send_rrdset(BACKEND_OPTIONS options, RRDSET *st);
extern BACKEND_OPTIONS backend_parse_data_source(const char *source, BACKEND_OPTIONS mode);

extern calculated_number backend_calculate_value_from_stored_data(
        RRDSET *st                  // the chart
        , RRDDIM *rd                // the dimension
        , time_t after              // the start timestamp
        , time_t before             // the end timestamp
        , uint32_t options          // BACKEND_SOURCE_* bitmap
        , time_t *first_timestamp   // the timestamp of the first point used in this response
        , time_t *last_timestamp    // the timestamp that should be reported to backend
);

#endif /* NETDATA_BACKENDS_H */
