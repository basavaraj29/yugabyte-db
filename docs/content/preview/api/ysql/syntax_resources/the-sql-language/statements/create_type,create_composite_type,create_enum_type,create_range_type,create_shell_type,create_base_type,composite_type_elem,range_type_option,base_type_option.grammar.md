```output.ebnf
create_type ::= create_composite_type
                | create_enum_type
                | create_range_type
                | create_shell_type
                | create_base_type

create_composite_type ::= CREATE TYPE type_name AS ( 
                          [ composite_type_elem [ , ... ] ] )

create_enum_type ::= CREATE TYPE type_name AS ENUM ( 
                     [ name [ , ... ] ] )

create_range_type ::= CREATE TYPE type_name AS RANGE  ( SUBTYPE = 
                      subtype [ , range_type_option [ ... ] ] )

create_shell_type ::= CREATE TYPE type_name

create_base_type ::= CREATE TYPE type_name (  INPUT = input_function , 
                      OUTPUT = output_function 
                     [ , base_type_option [ ... ] ]  )

composite_type_elem ::= attribute_name data_type [ COLLATE collation ]

range_type_option ::= SUBTYPE_OPCLASS = subtype_operator_class
                      | COLLATION = collation
                      | CANONICAL = canonical_function
                      | SUBTYPE_DIFF = subtype_diff_function

base_type_option ::= RECEIVE = receive_function
                     | SEND = send_function
                     | TYPMOD_IN = type_modifier_input_function
                     | TYPMOD_OUT = type_modifier_output_function
                     | INTERNALLENGTH = { internallength | VARIABLE }
                     | PASSEDBYVALUE
                     | ALIGNMENT = alignment
                     | STORAGE = storage
                     | LIKE = like_type
                     | CATEGORY = category
                     | PREFERRED = { TRUE | FALSE }
                     | DEFAULT = default_type_value
                     | ELEMENT = element
                     | DELIMITER = delimiter
                     | COLLATABLE = { TRUE | FALSE }
```
