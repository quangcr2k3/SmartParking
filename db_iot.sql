-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 08, 2024 at 09:54 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_iot`
--

-- --------------------------------------------------------

--
-- Table structure for table `card`
--

CREATE TABLE `card` (
  `id` varchar(50) NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `card`
--

INSERT INTO `card` (`id`, `created_at`) VALUES
('139ca811', '2024-10-20 12:34:04'),
('23ad67a9', '2024-10-20 12:34:04'),
('53525fa9', '2024-10-20 12:34:04'),
('93da93a6', '2024-10-20 12:34:04');

-- --------------------------------------------------------

--
-- Table structure for table `history`
--

CREATE TABLE `history` (
  `rfid` varchar(10) NOT NULL,
  `status` varchar(20) NOT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `history`
--

INSERT INTO `history` (`rfid`, `status`, `time`) VALUES
('23ad67a9', 'in', '2024-10-27 15:29:59'),
('139ca811', 'in', '2024-10-27 15:30:03'),
('23ad67a9', 'out', '2024-10-27 15:30:07'),
('53525fa9', 'in', '2024-10-27 15:30:11'),
('139ca811', 'out', '2024-10-27 15:30:16'),
('53525fa9', 'out', '2024-10-27 15:30:19'),
('03a6a4a6', 'not_valid', '2024-10-27 15:30:24'),
('d33b8396', 'not_valid', '2024-10-27 15:32:37'),
('53525fa9', 'in', '2024-10-27 15:37:51'),
('53525fa9', 'out', '2024-10-27 15:37:56'),
('53525fa9', 'in', '2024-10-27 16:40:06'),
('53525fa9', 'out', '2024-10-27 16:40:17'),
('53525fa9', 'in', '2024-10-27 17:10:59'),
('53525fa9', 'out', '2024-10-27 17:11:06'),
('139ca811', 'in', '2024-10-27 17:11:17'),
('139ca811', 'out', '2024-10-27 17:11:21'),
('23ad67a9', 'in', '2024-10-27 17:11:26'),
('23ad67a9', 'out', '2024-10-27 17:11:31'),
('139ca811', 'in', '2024-10-27 17:56:30'),
('23ad67a9', 'in', '2024-10-27 17:56:34'),
('53525fa9', 'in', '2024-10-27 17:56:37'),
('23ad67a9', 'out', '2024-10-27 17:56:41'),
('139ca811', 'out', '2024-10-27 17:56:45'),
('53525fa9', 'out', '2024-10-27 17:56:48'),
('03a6a4a6', 'not_valid', '2024-10-27 17:56:58'),
('93da93a6', 'in', '2024-10-27 17:57:04'),
('93da93a6', 'out', '2024-10-27 17:57:35'),
('93da93a6', 'in', '2024-10-27 17:57:55'),
('93da93a6', 'out', '2024-10-27 18:05:25'),
('93da93a6', 'in', '2024-10-27 18:05:28'),
('93da93a6', 'out', '2024-10-27 18:05:34');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `card`
--
ALTER TABLE `card`
  ADD PRIMARY KEY (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
