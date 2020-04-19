-- phpMyAdmin SQL Dump
-- version 4.6.6deb4
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost:3306
-- Tiempo de generación: 01-11-2019 a las 12:45:00
-- Versión del servidor: 10.1.37-MariaDB-0+deb9u1
-- Versión de PHP: 7.0.33-0+deb9u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `vc_clothing`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `characters`
--

CREATE TABLE `characters` (
  `id` int(11) NOT NULL,
  `gender` tinyint(1) NOT NULL DEFAULT '0',
  `base_skin` int(11) NOT NULL DEFAULT '14',
  `dffpath` varchar(128) NOT NULL,
  `txdpath` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `characters`
--

INSERT INTO `characters` (`id`, `gender`, `base_skin`, `dffpath`, `txdpath`) VALUES
(1, 0, 14, 'clothing/1/b0.dff', 'clothing/1/b0.txd'),
(2, 0, 14, 'clothing/2/b0.dff', 'clothing/2/b0.txd'),
(3, 0, 14, 'clothing/3/b0.dff', 'clothing/3/b0.txd'),
(4, 0, 14, 'clothing/4/b0.dff', 'clothing/4/b0.txd'),
(5, 0, 14, 'clothing/5/b0.dff', 'clothing/5/b0.txd'),
(6, 0, 14, 'clothing/6/b0.dff', 'clothing/6/b0.txd'),
(7, 1, 11, 'clothing/7/b0.dff', 'clothing/7/b0.txd'),
(8, 1, 11, 'clothing/8/b0.dff', 'clothing/8/b0.txd'),
(9, 1, 11, 'clothing/9/b0.dff', 'clothing/9/b0.txd'),
(10, 1, 11, 'clothing/10/b0.dff', 'clothing/10/b0.txd'),
(11, 1, 11, 'clothing/11/b0.dff', 'clothing/11/b0.txd'),
(12, 1, 11, 'clothing/12/b0.dff', 'clothing/12/b0.txd');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `characters_clothes`
--

CREATE TABLE `characters_clothes` (
  `id_character` int(11) NOT NULL,
  `id_clothe_type` int(11) NOT NULL,
  `base_skin` int(11) NOT NULL DEFAULT '14',
  `dffpath` varchar(128) NOT NULL,
  `txdpath` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `characters_clothes`
--

INSERT INTO `characters_clothes` (`id_character`, `id_clothe_type`, `base_skin`, `dffpath`, `txdpath`) VALUES
(1, 1, 247, 'clothing/1/b1.dff', 'clothing/1/b1.txd'),
(1, 2, 21, 'clothing/1/b2.dff', 'clothing/1/b2.txd'),
(1, 3, 299, 'clothing/1/b3.dff', 'clothing/1/b3.txd'),
(1, 4, 113, 'clothing/1/b4.dff', 'clothing/1/b4.txd'),
(1, 5, 223, 'clothing/1/b5.dff', 'clothing/1/b5.txd'),
(1, 6, 280, 'clothing/1/cop.dff', 'clothing/1/cop.txd'),
(2, 1, 247, 'clothing/2/b1.dff', 'clothing/2/b1.txd'),
(2, 2, 21, 'clothing/2/b2.dff', 'clothing/2/b2.txd'),
(2, 3, 299, 'clothing/2/b3.dff', 'clothing/2/b3.txd'),
(2, 4, 113, 'clothing/2/b4.dff', 'clothing/2/b4.txd'),
(2, 5, 223, 'clothing/2/b5.dff', 'clothing/2/b5.txd'),
(2, 6, 280, 'clothing/2/cop.dff', 'clothing/2/cop.txd'),
(3, 1, 247, 'clothing/3/b1.dff', 'clothing/3/b1.txd'),
(3, 2, 21, 'clothing/3/b2.dff', 'clothing/3/b2.txd'),
(3, 3, 299, 'clothing/3/b3.dff', 'clothing/3/b3.txd'),
(3, 4, 113, 'clothing/3/b4.dff', 'clothing/3/b4.txd'),
(3, 5, 223, 'clothing/3/b5.dff', 'clothing/3/b5.txd'),
(3, 6, 280, 'clothing/3/cop.dff', 'clothing/3/cop.txd'),
(4, 1, 247, 'clothing/4/b1.dff', 'clothing/4/b1.txd'),
(4, 2, 21, 'clothing/4/b2.dff', 'clothing/4/b2.txd'),
(4, 3, 299, 'clothing/4/b3.dff', 'clothing/4/b3.txd'),
(4, 4, 113, 'clothing/4/b4.dff', 'clothing/4/b4.txd'),
(4, 5, 223, 'clothing/4/b5.dff', 'clothing/4/b5.txd'),
(4, 6, 280, 'clothing/4/cop.dff', 'clothing/4/cop.txd'),
(5, 1, 247, 'clothing/5/b1.dff', 'clothing/5/b1.txd'),
(5, 2, 21, 'clothing/5/b2.dff', 'clothing/5/b2.txd'),
(5, 3, 299, 'clothing/5/b3.dff', 'clothing/5/b3.txd'),
(5, 4, 113, 'clothing/5/b4.dff', 'clothing/5/b4.txd'),
(5, 5, 223, 'clothing/5/b5.dff', 'clothing/5/b5.txd'),
(5, 6, 280, 'clothing/5/cop.dff', 'clothing/5/cop.txd'),
(6, 1, 247, 'clothing/6/b1.dff', 'clothing/6/b1.txd'),
(6, 2, 21, 'clothing/6/b2.dff', 'clothing/6/b2.txd'),
(6, 3, 299, 'clothing/6/b3.dff', 'clothing/6/b3.txd'),
(6, 4, 113, 'clothing/6/b4.dff', 'clothing/6/b4.txd'),
(6, 5, 223, 'clothing/6/b5.dff', 'clothing/6/b5.txd'),
(6, 6, 280, 'clothing/6/cop.dff', 'clothing/6/cop.txd'),
(7, 1, 13, 'clothing/7/b1.dff', 'clothing/7/b1.txd'),
(7, 2, 191, 'clothing/7/b2.dff', 'clothing/7/b2.txd'),
(7, 3, 216, 'clothing/7/b3.dff', 'clothing/7/b3.txd'),
(7, 4, 233, 'clothing/7/b4.dff', 'clothing/7/b4.txd'),
(7, 5, 211, 'clothing/7/b5.dff', 'clothing/7/b5.txd'),
(7, 6, 309, 'clothing/7/cop.dff', 'clothing/7/cop.txd'),
(8, 1, 13, 'clothing/8/b1.dff', 'clothing/8/b1.txd'),
(8, 2, 191, 'clothing/8/b2.dff', 'clothing/8/b2.txd'),
(8, 3, 216, 'clothing/8/b3.dff', 'clothing/8/b3.txd'),
(8, 4, 233, 'clothing/8/b4.dff', 'clothing/8/b4.txd'),
(8, 5, 211, 'clothing/8/b5.dff', 'clothing/8/b5.txd'),
(8, 6, 309, 'clothing/8/cop.dff', 'clothing/8/cop.txd'),
(9, 1, 13, 'clothing/9/b1.dff', 'clothing/9/b1.txd'),
(9, 2, 191, 'clothing/9/b2.dff', 'clothing/9/b2.txd'),
(9, 3, 216, 'clothing/9/b3.dff', 'clothing/9/b3.txd'),
(9, 4, 233, 'clothing/9/b4.dff', 'clothing/9/b4.txd'),
(9, 5, 211, 'clothing/9/b5.dff', 'clothing/9/b5.txd'),
(9, 6, 309, 'clothing/9/cop.dff', 'clothing/9/cop.txd'),
(10, 1, 13, 'clothing/10/b1.dff', 'clothing/10/b1.txd'),
(10, 2, 191, 'clothing/10/b2.dff', 'clothing/10/b2.txd'),
(10, 3, 216, 'clothing/10/b3.dff', 'clothing/10/b3.txd'),
(10, 4, 233, 'clothing/10/b4.dff', 'clothing/10/b4.txd'),
(10, 5, 211, 'clothing/10/b5.dff', 'clothing/10/b5.txd'),
(10, 6, 309, 'clothing/10/cop.dff', 'clothing/10/cop.txd'),
(11, 1, 13, 'clothing/11/b1.dff', 'clothing/11/b1.txd'),
(11, 2, 191, 'clothing/11/b2.dff', 'clothing/11/b2.txd'),
(11, 3, 216, 'clothing/11/b3.dff', 'clothing/11/b3.txd'),
(11, 4, 233, 'clothing/11/b4.dff', 'clothing/11/b4.txd'),
(11, 5, 211, 'clothing/11/b5.dff', 'clothing/11/b5.txd'),
(11, 6, 309, 'clothing/11/cop.dff', 'clothing/11/cop.txd'),
(12, 1, 13, 'clothing/12/b1.dff', 'clothing/12/b1.txd'),
(12, 2, 191, 'clothing/12/b2.dff', 'clothing/12/b2.txd'),
(12, 3, 216, 'clothing/12/b3.dff', 'clothing/12/b3.txd'),
(12, 4, 233, 'clothing/12/b4.dff', 'clothing/12/b4.txd'),
(12, 5, 211, 'clothing/12/b5.dff', 'clothing/12/b5.txd'),
(12, 6, 309, 'clothing/12/cop.dff', 'clothing/12/cop.txd');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `clothes_types`
--

CREATE TABLE `clothes_types` (
  `id` int(11) NOT NULL,
  `type` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `clothes_types`
--

INSERT INTO `clothes_types` (`id`, `type`) VALUES
(1, 'BODY_1'),
(2, 'BODY_2'),
(3, 'BODY_3'),
(4, 'BODY_4'),
(5, 'BODY_5'),
(6, 'BODY_6'),
(7, 'POLICE');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `characters_clothes`
--
ALTER TABLE `characters_clothes`
  ADD PRIMARY KEY (`id_character`,`id_clothe_type`),
  ADD KEY `id_clothe_type` (`id_clothe_type`);

--
-- Indices de la tabla `clothes_types`
--
ALTER TABLE `clothes_types`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `characters`
--
ALTER TABLE `characters`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;
--
-- AUTO_INCREMENT de la tabla `clothes_types`
--
ALTER TABLE `clothes_types`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `characters_clothes`
--
ALTER TABLE `characters_clothes`
  ADD CONSTRAINT `characters_clothes_ibfk_1` FOREIGN KEY (`id_character`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `characters_clothes_ibfk_2` FOREIGN KEY (`id_clothe_type`) REFERENCES `clothes_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
