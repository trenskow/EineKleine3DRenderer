// swift-tools-version:6.0

//
//  Package.swift
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 10/11/2024.
//

import PackageDescription

let package = Package(
    name: "EineKleine3DRenderer",
    products: [
        .library(
            name: "EineKleine3DRenderer", 
            targets: ["EineKleine3DRenderer"]),
    ],
    targets: [
        .target(
            name: "EineKleine3DRenderer",
            dependencies: [],
            path: ".",
            publicHeadersPath: "./include")
    ],
    cxxLanguageStandard: .cxx17
)
