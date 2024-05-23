project('Cub3D', 'c', version : '1.0.0')

cc = meson.get_compiler('c')
cmake = import('cmake')

libm = cc.find_library('m')
libft = subproject('ft').get_variable('dep')
libgnl = subproject('gnl').get_variable('dep')
libmlx = cmake.subproject('mlx').dependency('mlx42')

src = files(
    'src/main.c',
    'src/file.c',
    'src/loop.c',
    'src/hook.c'
)

inc = include_directories('include')

executable('cub3D', src,
    include_directories : inc,
    dependencies : [libm, libft, libgnl, libmlx],
)
