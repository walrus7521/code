__float_bins__ = True

capacity = 4 # lbs

items = [
    # name,                 days, priority
    ('westminster abbey',   0.5,    7),
    ('globe theater',       0.5,    6),
    ('national gallery',    1,      9),
    ('british museum',      2,      9),
    ('st. pauls cathedral', 0.5,    8),
    ]

# capacity columns independent of column index
col_wts = [0.5, 1, 1.5, 2] # day bins

# float version
def TO_INDEX(x):
    return (round(x))


