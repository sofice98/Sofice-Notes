package com.ay.dao;

import com.ay.model.AyRole;
import com.ay.model.AyUser;
import org.springframework.stereotype.Repository;

@Repository
public interface AyRoleDao {

    AyRole findById(String id);
//    @Select("SELECT * FROM ay_user")
//    List<AyUser> findAll();
//    @Select("SELECT * FROM ay_user")
//    @Results({
//            @Result(id = true,column = "id",property = "id"),
//            @Result(column = "name",property = "name"),
//            @Result(column = "password",property = "password")
//    })
//    List<AyUser> findAll();

//    @Select("SELECT * FROM ay_user WHERE id = #{id}")
    //AyRole findById(String id);
//
//    @Select("SELECT * FROM ay_user WHERE name = #{name}")
//    List<AyUser> findByName(String name);
//
//    int countByName(String name);
//
//    @Insert("INSERT INTO ay_user(name,password) VALUES(#{name}, #{password})")
//    @Options(useGeneratedKeys = true, keyProperty = "id")
//    int insert(AyUser ayUser);
//
//    @Update("UPDATE  ay_user SET name = #{name}, password = #{password} WHERE id = #{id}")
//    int update(AyUser ayUser);
//
//    @Delete("DELETE FROM ay_user WHERE id = #{id}")
//    int delete(int id);
//
//    @Delete("DELETE FROM ay_user WHERE name = #{name}")
//    int deleteByName(String name);

//    @Select("SELECT * FROM ay_user WHERE name = #{name} and password = #{password}")
//    List<AyUser> findByNameAndPassword(@Param("name") String name,@Param("password")String password);

//    List<AyUser> findByNameAndPassword(String name,String password);

//  List<AyUser> findByNameAndPassword(Map<String, String > map);

//    List<AyUser> findByIds(@Param("list") List<Integer> list);
}
