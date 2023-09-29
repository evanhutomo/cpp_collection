function(kotobakoe_message msg)
    if (NOT USE_QUIET)
        message(STATUS ${msg})
    endif()
endfunction()

kotobakoe_message("┌─ kotobakoe options ─────────────────")
kotobakoe_message("│ USE_DEBUG          : ${USE_DEBUG}")
kotobakoe_message("│ USE_LINUX_ENV      : ${USE_LINUX_ENV}")
kotobakoe_message("│ USE_QUIET          : ${USE_QUIET}")
kotobakoe_message("└─────────────────────────────────────")