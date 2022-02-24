package com.ay.test;

import com.ay.dao.AyUserDao;
import com.ay.model.AyUser;
//import com.github.pagehelper.PageHelper;
//import com.github.pagehelper.PageInfo;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.junit.Test;
import org.mybatis.spring.SqlSessionFactoryBean;

import javax.annotation.Resource;
import java.util.List;

/**
 * 描述：用户DAO测试类
 *
 * @author Ay
 * @create 2018/05/04
 **/
public class AyUserDaoTest{

    @Resource
    private AyUserDao ayUserDao;

    @Test
    public void testFindAll(){
//        System.out.println("你好司展宇");
        List<AyUser> userList = ayUserDao.findAll();
        System.out.println(userList.size());
    }


}
